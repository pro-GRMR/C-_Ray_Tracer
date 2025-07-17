#pragma once
template <typename T>
class Array2D
{
private:
    unsigned w, h;
    T* arr;

public:
    // Construct a new array with the given width and height.
    Array2D(unsigned width, unsigned height) : w(width), h(height), arr(new T[width * height]) {}

    Array2D(const Array2D &) = delete;

    // Delete an array
    ~Array2D()
    {
        delete[] arr;
    }

    // Get the width of the array
    unsigned get_width() const
    {
        return w;
    }

    // Get the height of the array
    unsigned get_height() const
    {
        return h;
    }

    // Get an element from the array given horizontal and vertical position
    // Behavior may be undefined if the element is not set
    T get(unsigned x, unsigned y) const
    {
        return arr[x + y * w];
    }

    // Set an element of the array given a horizontal and vertical position
    void set(unsigned x, unsigned y, T value)
    {
        arr[x + y * w] = value;
    }
};
