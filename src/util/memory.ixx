export module util.memory;

import <memory>;
import <vector>;

export template <typename T> using UPtr = std::unique_ptr<T>;
export template <typename T> using SPtr = std::shared_ptr<T>;
export template <typename T>
using RefVector = std::vector<std::reference_wrapper<T>>;
export template <typename T> using SPtrVector = std::vector<SPtr<T>>;
export template <typename T> using UPtrVector = std::vector<UPtr<T>>;