#pragma once

#include "./common.h"

#include "./event.h"
#include "./exception.h"

namespace cq {
    struct ApiError : RuntimeError {
        int code;
        ApiError(const int code) : RuntimeError("failed to call coolq api") { this->code = code; }

        static const auto INVALID_DATA = 100;
        static const auto INVALID_TARGET = 101;
        static const auto INVALID_ARGS = 102;
    };

    void __init_api();

    int64_t send_private_message(const int64_t user_id, const std::string &message);
    int64_t send_group_message(const int64_t group_id, const std::string &message);
    int64_t send_discuss_message(const int64_t discuss_id, const std::string &message);

    inline int64_t send_message(const Target &target, const std::string &message) {
        if (target.group_id.has_value()) {
            return send_group_message(target.group_id.value(), message);
        }
        if (target.discuss_id.has_value()) {
            return send_discuss_message(target.discuss_id.value(), message);
        }
        if (target.user_id.has_value()) {
            return send_private_message(target.user_id.value(), message);
        }
        throw ApiError(ApiError::INVALID_TARGET);
    }

    void delete_msg(const int64_t message_id);

    void send_like(const int64_t user_id, const int32_t times = 1);

    void set_group_kick(const int64_t group_id, const int64_t user_id, const bool reject_future_request);
    void set_group_ban(const int64_t group_id, const int64_t user_id, const int64_t duration);
    void set_group_anonymous_ban(const int64_t group_id, const std::string &flag, const int64_t duration);
    void set_group_whole_ban(const int64_t group_id, const bool enable);
    void set_group_admin(const int64_t group_id, const int64_t user_id, const bool enable);
    void set_group_anonymous(const int64_t group_id, const bool enable);
    void set_group_card(const int64_t group_id, const int64_t user_id, const std::string &card);
    void set_group_leave(const int64_t group_id, const bool dismiss);
    void set_group_special_title(const int64_t group_id, const int64_t user_id, const std::string &special_title,
                                 const int64_t duration);
    void set_discuss_leave(const int64_t discuss_id);

    void set_friend_request(const std::string &flag, const RequestEvent::Operation operation,
                            const std::string &remark = "");
    void set_group_request(const std::string &flag, const std::string &sub_type,
                           const RequestEvent::Operation operation, const std::string &reason = "");

    int64_t get_login_user_id();
    std::string get_login_nickname();

    std::string get_cookies(const std::string &domain = "");
    int32_t get_csrf_token();
    std::string get_app_directory();

    std::string get_record(const std::string &file, const std::string &out_format, const bool full_path = true);
    std::string get_image(const std::string &file);
    bool can_send_image();
    bool can_send_record();
} // namespace cq