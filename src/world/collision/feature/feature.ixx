export module world.collision.feature.feature;

// import <concepts>;

export class Collider;

// export template <typename T>
// concept IsFeature = requires(T t) {
//   { t.parent } -> std::same_as<const Collider &>;
//   { t.ID } -> std::same_as<const unsigned short &>;
// };

export class Feature {
public:
  const Collider &parent;
  const unsigned short ID;

  virtual void finishCreation() = 0;

  bool operator==(const Feature &other) const;

protected:
  Feature(const Collider &parent, const unsigned short ID);
};