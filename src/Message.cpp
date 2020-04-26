#include "Message.h"

#include <algorithm>

void MessageView::tokenizeMessage(const std::string_view& msg, std::vector<std::string_view>& tokens) {
    auto beg = 0;
    while (true) {
        auto end = msg.find_first_of("\n", beg);
        if (end == msg.npos)
            break;

        if (end != beg)
            tokens.emplace_back(msg.data() + beg, end - beg);

        beg = end + 1;
    }
}

MessageView::MessageView(const char* buffer, int bufferSize) : message_() {
    std::string_view full_view(buffer, bufferSize);

    constexpr char* messageStartMagic = "[MESSAGE]";
    constexpr char* messageEndMagic = "[END]";

    const auto begin = full_view.find(messageStartMagic);
    const auto end = full_view.find(messageEndMagic) + strlen(messageEndMagic);
    if ((begin == full_view.npos) || (end == full_view.npos))
        return;//buffer doesn't contain complete message

    message_ = std::string_view(buffer + begin, end - begin);
    
    tokenizeMessage(message_, messageTokens);
}

const std::string_view& MessageView::message() const {
    return message_;
}

const std::vector<std::string_view>& MessageView::tokens() const{
    return messageTokens;
}

void MessageView::print() const {
    const auto& tokens_ = tokens();
    if (tokens_.size() != 10)
        return;

    printf("%-*.*s | %-*.*s | %-.*s\n", 
        15, tokens_.at(7).size(), tokens_.at(7).data(), 
        25, tokens_.at(8).size(), tokens_.at(8).data(), 
        tokens_.at(9).size(), tokens_.at(9).data());
}
