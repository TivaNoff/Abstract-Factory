#include <iostream>
#include <memory>
#include <string>

// Абстрактний продукт: Кнопка
class Button {
public:
    virtual ~Button() = default;
    virtual void paint() const = 0;
};

// Абстрактний продукт: Прапорець (checkbox)
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void paint() const = 0;
};

// Конкретний продукт: Кнопка у стилі Windows
class WindowsButton : public Button {
public:
    void paint() const override {
        std::cout << "WindowsButton painted." << std::endl;
    }
};

// Конкретний продукт: Прапорець у стилі Windows
class WindowsCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "WindowsCheckbox painted." << std::endl;
    }
};

// Конкретний продукт: Кнопка у стилі Mac
class MacButton : public Button {
public:
    void paint() const override {
        std::cout << "MacButton painted." << std::endl;
    }
};

// Конкретний продукт: Прапорець у стилі Mac
class MacCheckbox : public Checkbox {
public:
    void paint() const override {
        std::cout << "MacCheckbox painted." << std::endl;
    }
};

// Абстрактна фабрика
class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// Конкретна фабрика для Windows-інтерфейсу
class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

// Конкретна фабрика для Mac-інтерфейсу
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

int main() {
    // Припустимо, ми хочемо використати Windows-стиль
    std::unique_ptr<GUIFactory> factory = std::make_unique<WindowsFactory>();

    // Використання фабрики для створення продуктів
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();

    button->paint();      // WindowsButton painted.
    checkbox->paint();    // WindowsCheckbox painted.

    // Тепер, якщо ми хочемо Mac-стиль, досить замінити фабрику:
    factory = std::make_unique<MacFactory>();

    button = factory->createButton();
    checkbox = factory->createCheckbox();

    button->paint();      // MacButton painted.
    checkbox->paint();    // MacCheckbox painted.

    return 0;
}
