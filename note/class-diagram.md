classDiagram
    class User{
        string nickName
        string userName
        poll struct
        bool operator
    }
    class Channel{
        string name
        string topic
        string password
        int mode
        vector<User*> user
    }
    class Server{
        Array<User> users
        vector<Channel> channels
        poll struct[MAXUSER]
        int channelCount
        int userCount
        std::string password
        int socket
        initServer()
        serverRoutine()
    }
    Server--* Channel
    Server--* User