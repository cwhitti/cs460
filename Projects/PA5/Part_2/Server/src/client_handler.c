#include "client_handler.h"

// join function
void clientJoin( ChatNodeList *clientList, Message* messageObj )
{
  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  // add client to clientList
    // function: addChatNodeToList
  addChatNodeToList(clientList, &clientNode);

  // change msgtype from JOIN > JOINED
  messageObj->messageType = JOINING;

  // send join message to all clients
    // function: forwardMessage()
  forwardMessage(clientList, messageObj);
}

// leave function
void clientLeave( ChatNodeList *clientList, Message* messageObj )
{
  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  // remove chat node
    // function: removeNodeFromList
  if (removeNodeFromList(clientList, &clientNode))
  {
    // change msgtype from LEAVE > LEAVING
    messageObj->messageType = LEAVING;

    // send
      // function: forwardMessage()
    forwardMessage(clientList, messageObj);
  }
}

void forwardMessage( ChatNodeList *clientList, Message* messageObj )
{
   // declare variables
  ChatNode* wkgPtr;

  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  // loop through clientList
  for (wkgPtr = clientList->firstPtr; wkgPtr != NULL; wkgPtr = wkgPtr->next)
    // if the current client != clientNode
    // function: compareChatNodes()
    if ( !compareChatNodes(wkgPtr, &clientNode) )
    {
      // send message to everyone
        // function: writeMessageToSocket( note )
      int sendSocket = socket(AF_INET, SOCK_STREAM, 0);;

      struct sockaddr_in clientAddress;
      clientAddress.sin_family = AF_INET;
      clientAddress.sin_addr.s_addr = htonl(wkgPtr->ip); 
      clientAddress.sin_port = htons(wkgPtr->port); 

      if (connect(sendSocket, (struct sockaddr *)&clientAddress,
                                                sizeof(clientAddress)) != -1)
      {
        writeMessageToSocket(sendSocket, messageObj);
      }
    }
}

/*
// note function
void clientNote( ChatNodeList *clientList, Message* messageObj )
{
  // declare variables
  ChatNode* wkgPtr;

  // grab client from messageObj
  ChatNode clientNode = messageObj->messageSender;

  // loop through clientList
  for (wkgPtr = clientList->firstPtr; wkgPtr != NULL; wkgPtr = wkgPtr->next)
    // if the current client != clientNode
    // function: compareChatNodes()
    if ( !compareChatNodes(wkgPtr, &clientNode) )
    {
      // send message to everyone
        // function: writeMessageToSocket( note )
      int sendSocket = socket(AF_INET, SOCK_STREAM, 0);;

      struct sockaddr_in clientAddress;
      clientAddress.sin_family = AF_INET;
      clientAddress.sin_addr.s_addr = htonl(wkgPtr->chat_node.ip); 
      clientAddress.sin_port = htons(wkgPtr->chat_node.port); 

      if (connect(send, (struct sockaddr *)&clientAddress,
                                                sizeof(clientAddress)) != -1)
      {
        writeMessageToSocket(sendSocket, messageObj);
      }
    }
}

// joining function
void globalJoining( ChatNodeList *clientList, Message* messageObj )
{
  // "(!) [USER] has joined."
  ChatNode* wkgPtr;
  ChatNode clientNode = messageObj->messageSender;

  // iterate through clientList
  for (wkgPtr = clientList->firstPtr; wkgPtr != NULL; wkgPtr = wkgPtr->next)
  {
    if ( !compareChatNodes(wkgPtr &clientNode) )
    {
      // send message to everyone
        // function: writeMessageToSocket( note )
      int sendSocket = socket(AF_INET, SOCK_STREAM, 0);;

      struct sockaddr_in clientAddress;
      clientAddress.sin_family = AF_INET;
      clientAddress.sin_addr.s_addr = htonl(wkgPtr->chat_node.ip); 
      clientAddress.sin_port = htons(wkgPtr->chat_node.port); 

      if (connect(send, (struct sockaddr *)&clientAddress,
                                                sizeof(clientAddress)) != -1)
      {
        writeMessageToSocket(sendSocket, messageObj);
      }
    }
  }
}

// leaving function
void globalLeaving( ChatNodeList *clientList, Message* messageObj )
{
  // "(!) [USER] has left."

  // iterate through clientList

    // check if current client != sending client

      // send message to client
        // function: writeMessageToSocket( messageObj )

}

void globalShutdown( ChatNodeList *clientList, Message* messageObj )
{
  // "(!) Shutting Down..."

  // iterate through clientList

    // send message to everyone
      // function: writeMessageToSocket

  // clear list
    // function: clearChatNodeList
}
*/
void* handle_client( void* args )
{
  // initialize variables
  ThreadArgs *threadArgs = (ThreadArgs *)args;


  // grab client socket
  int clientSocket = threadArgs->clientSocket;
  // grab clientList
  ChatNodeList* clientList = threadArgs->clientList;

  // read entire message from socket, returns pointer to new msg struct
    // function: readMessageFromSocket( )
  Message* messageObj = readMessageFromSocket( clientSocket );

  // process depending on MessageType
  switch (messageObj->messageType)
  {
    //  JOIN
    case JOIN:
      // function: clientJoin()
      clientJoin(clientList, messageObj);

    //  LEAVE
    case LEAVE:
      // function: clientLeave()
      clientLeave(clientList, messageObj);

    //  SHUTDOWN
    case SHUTDOWN:
      // function: clientLeave()
      clientLeave(clientList, messageObj);

    //  SHUTDOWN_ALL
    case SHUTDOWN_ALL:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);

      // function: clearChatNodeList()
      clearChatNodeList(clientList);

    //  NOTE
    case NOTE:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);

    //  JOINING
    case JOINING:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);

    //  LEAVING
    case LEAVING:
      // function: forwardMessage()
      forwardMessage(clientList, messageObj);
  }
}
