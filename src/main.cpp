#include "FileLogger.h"
#include "Connection.h"
#include "Message.h"

#include <Windows.h>

void statusPrintLine(const char* msg);
void statusPrintLine(const std::string& str);
void fatalError(const char* msg);
bool syncWithParent();

int main() {
    printf("%s\n\n", "TraceSink server for Glacier 2 by B3");

    constexpr int recvBufSize = 0x6000;
    auto recvBuf = std::make_unique<char[]>(recvBufSize);
    
    if (!syncWithParent())
        fatalError("Failed to sync with parent");
    statusPrintLine("Synced with parent");

    Connection connection;
    if(!connection.isOpen())
        fatalError("Failed to connect to parent");
    statusPrintLine("Connected with parent");

    FileLogger logger;
    if(!logger.isOpen())
        fatalError("Failed to initilize file logger");
    statusPrintLine("Logging to " + logger.path().generic_string() + "...\n\n");

    int recvSize = 0;
    do {
        recvSize = connection.receive(recvBuf.get(), recvBufSize);
        if (recvSize <= 0)
            continue;

        MessageView msg(recvBuf.get(), recvSize);
        msg.print();
        logger.write(msg.message().data(), msg.message().size());

    } while (recvSize > 0);

    statusPrintLine("Connection closed");

    return 0;
}

bool syncWithParent() {
    constexpr char* TRACE_SINK_PROCESS_APPLICATION_STARTED_EVENT_NAME = R"(Global\{1D03C19C-B5EF-4cb0-93CC-C53C5937482E}:TraceSinkStartedEvent)";

    HANDLE event = OpenEventA(EVENT_MODIFY_STATE, false, TRACE_SINK_PROCESS_APPLICATION_STARTED_EVENT_NAME);
    if (!event)
        return false;

    if (!SetEvent(event))
        return false;

    //Event will be destroyed by parent
    return true;
}

void statusPrintLine(const char* msg) {
    std::string message = "TRACE_SINK: ";
    message += msg;

    printf("%s\n", message.c_str());
    OutputDebugStringA(message.c_str());
}

void statusPrintLine(const std::string& str) {
    statusPrintLine(str.c_str());
}

void fatalError(const char* msg) {
    statusPrintLine(msg);
    exit(1);
}
