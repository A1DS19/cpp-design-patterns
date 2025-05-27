#pragma once

#include <cstdint>
#include <string>
#include <utility>

// Summary
// struct Config groups parameters and makes one neat package.

// = default gives you the normal copy/move behavior without hand-writing it.

// explicit stops surprise conversions; you have to ask out loud to make a
// Product.

// std::move marks things as “stealable,” so the compiler can do a cheap pointer
// swap instead of a full copy.

class Product {
public:
  struct Config {
    std::string name;
    float price;
    uint16_t quantity;
  };

private:
  Config _cfg;

  explicit Product(Config cfg) noexcept : _cfg(std::move(cfg)) {}

public:
  // Defaulted copy/move
  Product(const Product &) = default;
  Product(Product &&) noexcept = default;
  Product &operator=(const Product &) = default;
  Product &operator=(Product &&) noexcept = default;

  // Queries
  bool is_available() const noexcept { return _cfg.quantity > 0; }
  const std::string &name() const noexcept { return _cfg.name; }
  float price() const noexcept { return _cfg.price; }
  uint16_t quantity() const noexcept { return _cfg.quantity; }

  // Builder for Product
  class Builder {
  private:
    Config _cfg;

  public:
    // Required parameters
    Builder(std::string name, float price, uint16_t quantity) noexcept
        : _cfg{std::move(name), price, quantity} {}

    // Fluent setters
    Builder &setName(std::string name) noexcept {
      _cfg.name = std::move(name);
      return *this;
    }

    Builder &setPrice(float price) noexcept {
      _cfg.price = price;
      return *this;
    }

    Builder &setQuantity(uint16_t quantity) noexcept {
      _cfg.quantity = quantity;
      return *this;
    }

    // Build the final Product
    Product build() noexcept { return Product{std::move(_cfg)}; }
  };

  // Convenient entry point
  static Builder create(std::string name, float price,
                        uint16_t quantity) noexcept {
    return Builder{std::move(name), price, quantity};
  }
};
