include(FetchContent)

message("DiscordRPC")
FetchContent_Declare(
    DiscordRPC
    GIT_REPOSITORY https://github.com/discord/discord-rpc.git
    GIT_TAG        v3.4.0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(DiscordRPC)