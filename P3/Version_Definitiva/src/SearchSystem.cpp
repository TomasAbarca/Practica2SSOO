#include "SearchSystem.h"


int SearchSystem::search(SearchRequest sr, Client client, std::string book, int limit, std::priority_queue<LineResult, std::vector<LineResult>, OrderQueue> &pq_pointer)
{
    std::priority_queue<LineResult, std::vector<LineResult>,OrderQueue> new_pq;
	int limit_aux = limit;
	int i;
	std::vector<std::string> arrayLine;

	arrayLine = readFile(book);

	if(arrayLine.size() != 0){			   /* If the arrayLine size is bigger than 0, then delete the last line of the file */
		arrayLine.erase(arrayLine.end());  /* Delete the last line of the file */
	}					

	for(i = 0; i < arrayLine.size(); i++){					/* Do the search in every .txt */
			new_pq = searchTheWord(divideLineInWords(arrayLine[i]), sr.get_word_to_search(), i, 1, 0, arrayLine.size(), new_pq);
	}
	
	while(limit_aux != 0 && new_pq.size() > 0){
		limit_aux--;
		LineResult search = new_pq.top();
		new_pq.pop();								/* Delete the top of the new priority queue */
		pq_pointer.push(search);
		if(limit_aux == 0 && client.get_category() == "Free Account"){			/* If a FREE client has limit = 0... */
			std::cout << COLOR_GREEN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
			std::cout << COLOR_GREEN << "FREE client with id " << client.get_id_client() << " without searchs." << std::endl;
			std::cout << COLOR_GREEN << "--------------------------------------------------------------------------------------" << std::endl;
		}else if(limit_aux == 0 && client.get_category()  == "Premium Limit"){		/* If a PRIME client has limit = 0... */
			std::cout << COLOR_GREEN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
			std::cout << COLOR_GREEN << "PRIME client with id " << client.get_id_client() << " without balance." << std::endl;
			std::cout << COLOR_GREEN << "--------------------------------------------------------------------------------------" << std::endl;
			PaymentReload pr(client.get_id_client());				/* Create a PaymentReload */
			std::lock_guard<std::mutex> lk(g_sem_paymentRequest);
			g_paymentReload_queue.push(std::move(pr));			/* Push it to the payment_queue */
			g_wait_paySystem.notify_one();					/* Notify one PaySystem */
			limit_aux = g_paymentReload_queue.front().client_future.get();	/* Get the new limit for the client */
			g_paymentReload_queue.pop();
			g_wait_paySystem.notify_all();					
		}
	}
	return limit_aux;
}

Client SearchSystem::get_client(int id_client)
{
    bool find = false;
	int i;

	Client c(0,"","");

	for(i = 0; i < g_clients.size() && !find; i++){
		if(g_clients[i].get_id_client() == id_client){
			Client c = g_clients[i];
			find = true;
			return c;
		}
	}
	return c;
}

SearchRequest SearchSystem::get_search_request()
{
    int position = 0;
	int random_num;

	srand(time(NULL));

	SearchRequest search_request(-1,"",-1);

	if(g_searchRequest_vector.same_priority() == true){
		SearchRequest sr = g_searchRequest_vector.front();
		search_request = sr;
		g_searchRequest_vector.pop();
	}else{
		random_num = 1 + rand()%(11-1);
		if(random_num <= 8){
			position = g_searchRequest_vector.get_pos_premium_request();
			SearchRequest sr = g_searchRequest_vector.get_request_by_pos(position);
			search_request = sr;
		}else{
			position = g_searchRequest_vector.get_pos_free_request();
			SearchRequest sr = g_searchRequest_vector.get_request_by_pos(position);
			search_request = sr;
		}
		g_searchRequest_vector.del_request_by_pos(position);		
	}

	return search_request;
}

void SearchSystem::search_on_book(SearchRequest sr)
{
    Client client = get_client(sr.get_id_client());
	int limit = client.get_limit();
	int i;
				
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));	/* Delay of 1 second to pause the program */
	
	for(i = 0; i < g_books.size(); i++){
		limit = search(sr, client, g_books[i], limit, std::ref(pq_vector[i]));
	}
}

void SearchSystem::fill_pq_vector()
{
	int i;
    std::priority_queue<LineResult, std::vector<LineResult>,OrderQueue> pq;
	
	for(i = 0; i < g_books_num; i++){
			pq_vector.push_back(pq);
	}
}

void SearchSystem::operator()()
{
    while(1){
		/* Fill the vector of priority queues */
		fill_pq_vector();
			
		std::unique_lock<std::mutex> ul(g_sem_searchSystem);
		/* The SearchSystem will be blocked if the queue of the search request is empty */
		g_wait_searchSystem.wait(ul, [] {return (g_searchRequest_vector.get_v_request().size() != 0);});	
		ul.unlock();
		/* Get the front SearchRequest of the vector */
		g_sem_searchRequest.lock();
		SearchRequest search_request = get_search_request();
		g_sem_searchRequest.unlock();
		std::cout << COLOR_GREEN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
		std::cout << COLOR_GREEN "Searching the word " << search_request.get_word_to_search() << " in all the texts for the user with id " << search_request.get_id_client() << std::endl;
		std::cout << COLOR_GREEN << "--------------------------------------------------------------------------------------" << std::endl;
		search_on_book(search_request);
				
		std::cout << COLOR_GREEN << "\n------------------------------------ SEARCH SYSTEM -----------------------------------" << std::endl;
		std::cout << COLOR_GREEN <<"The search request of the user with id " << search_request.get_id_client() << " has been completed, the results will be send." << std::endl;
		std::cout << COLOR_GREEN << "--------------------------------------------------------------------------------------" << std::endl;
					
		/* When the SearchRequest has been completed, a ReplySearch is created and inserted in the reply_search_vector */
		MediatorySearch mediatory_search(search_request.get_id_client(), pq_vector);
		g_mediatory_vector.insert(mediatory_search);
		/* Notify all wait_user condition variable to unlock the user */
		g_wait_client.notify_all();
		/* Notify one wait_search condition variable to unlock other SearchSystem */
		g_wait_searchSystem.notify_one();
	}	
}