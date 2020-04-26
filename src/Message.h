#pragma once

#include <string_view>
#include <vector>

class MessageView {
private:
    std::string_view message_;
    std::vector<std::string_view> messageTokens;

    void tokenizeMessage(const std::string_view& msg, std::vector<std::string_view>& tokens);

public:
    MessageView(const char* buffer, int bufferSize);

    const std::string_view& message() const;
    const std::vector<std::string_view>& tokens() const;

    void print() const;
};