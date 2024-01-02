export module util.debug;

export import <iostream>;
export import <format>;

export template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  std::cout << std::format("{}\n",
                           std::format(str, std::forward<Args>(args)...));
}