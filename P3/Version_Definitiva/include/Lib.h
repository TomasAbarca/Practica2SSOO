#define CLIENTS 10
#define CONCURRENT_CLIENTS 4
#define LIMIT 50 // Variable that can be used as credits and limit of words
#define FILE_WORD "Words.txt"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

std::condition_variable g_wait_paySystem;
std::condition_variable g_wait_searchSystem;
std::condition_variable g_wait_client;

std::vector<std::string> g_dictionary = {};
std::vector<std::string> g_books = {"17-LEYES-DEL-TRABJO-EN-EQUIPO.txt", "21-LEYES-DEL-LIDERAZGO.txt"};

std::atomic<int> g_id_request (0);

int g_books_num = 0;

std::mutex g_sem_searchSystem;
std::mutex g_sem_paySystem;
std::mutex g_sem_paymentRequest;
std::mutex g_sem_client;
std::mutex g_sem_searchRequest;
