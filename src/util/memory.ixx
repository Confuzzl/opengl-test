export module util.memory;

import <memory>;

export template <typename T> using UPtr = std::unique_ptr<T>;
export template <typename T> using SPtr = std::shared_ptr<T>;
