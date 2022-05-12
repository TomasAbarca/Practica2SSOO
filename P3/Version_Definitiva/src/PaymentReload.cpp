class PaymentReload{
    public:
        int id_client;
        std::promise<int> client_promise;
        std::future<int> client_future;

        PaymentReload(int id_client): id_client(id_client){
            client_future = client_promise.get_future();
        };
};