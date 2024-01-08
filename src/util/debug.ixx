export module util.debug;

export import <iostream>;
export import <format>;

export void println(const std::string &str) { std::cout << str << "\n"; }

export template <typename... Args>
void println(std::format_string<Args...> str, Args &&...args) {
  println(std::format(str, std::forward<Args>(args)...));
}