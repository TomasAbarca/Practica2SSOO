/* In this class we present the pay system. It will be blocked until
*  we get a payment request. The objective is to set a new credit when the
*  client need it*/

#ifndef PAYSYSTEM_H
#define PAYSYSTEM_H

class PaySystem{
    public:
        Client get_client(int id_client);
        void operator()();
};

#endif