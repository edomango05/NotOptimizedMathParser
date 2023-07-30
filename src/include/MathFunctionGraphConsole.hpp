#ifndef MATH_FUNC_GRAPH_CONSOLE_H
#define MATH_FUNC_GRAPH_CONSOLE_H

#include <iostream>
#include <cmath>
#include <functional>
#include <assert.h>

using std::cout;
using std::endl;

enum VectorState : uint8_t
{
    NUll,
    Continue,
    Approximate,
    Intersection
};

namespace mfgc
{
    template <typename F, typename Res, typename... Args>
    concept invocable_result = requires(F &&f, Args &&...args) {
                                   {
                                       std::invoke(std::forward<F>(f), std::forward<Args>(args)...)
                                       } -> std::same_as<Res>;
                               };

    template <invocable_result<double, double> Fn>
    VectorState *graph(int _width, double unit, Fn f)
    {
        VectorState *arr = new VectorState[_width * _width];
        for (size_t i = 0; i < _width * _width; ++i)
        {
            arr[i] = VectorState::NUll;
        }
        int quad = (int)(_width / 2) * unit;
        const int axis = std::ceil(_width / 2);
        int lastY = -1;
        int lastX = -1;
        bool lastExists = false;
        for (int j = -_width / 2; j <= _width / 2; ++j)
        {
            int y = std::round(f(j * unit) / unit);
            if (y <= quad && y >= -quad)
            {
                if (y < 0)
                {
                    y = std::abs(y) + _width / 2;
                }
                else
                {
                    y = std::abs(y - _width / 2);
                }
                if (lastY != -1)
                {
                    if (lastExists)
                    {
                        if (lastY > y)
                        {
                            for (int dy = 1; dy < lastY - y; ++dy)
                            {
                                arr[(dy + y) * _width + lastX + 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                        else if (lastY < y)
                        {
                            for (int dy = 1; dy < y - lastY; ++dy)
                            {
                                arr[(dy + lastY) * _width + lastX + _width / 2] = VectorState::Approximate;
                            }
                        }
                    }
                    else
                    {
                        int yCopy = std::round(f((j - 1) * unit + 0.000001) / unit);
                        if (yCopy < 0)
                        {
                            for (int dy = y + 1; dy < _width; ++dy)
                            {
                                arr[dy * _width + j - 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                        else
                        {
                            for (int dy = y - 1; dy >= 0; --dy)
                            {
                                arr[dy * _width + j - 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                    }
                }
                lastY = y;
                lastX = j;
                lastExists = true;
                arr[y * _width + j + _width / 2] = VectorState::Continue;
            }
            else
            {
                if (lastExists)
                {
                    lastExists = false;
                    y = std::round(f(j * unit - 0.000001) / unit);
                    if (y < 0)
                    {
                        for (int dy = lastY + 1; dy < _width; ++dy)
                        {
                            arr[dy * _width + j + _width / 2] = VectorState::Approximate;
                        }
                        lastY = _width;
                    }
                    else
                    {
                        for (int dy = lastY - 1; dy >= 0; --dy)
                        {
                            arr[dy * _width + j + _width / 2] = VectorState::Approximate;
                        }
                        lastY = 0;
                    }
                }
                else
                {
                    lastExists = false;
                    if (y < 0)
                    {
                        lastY = _width;
                    }
                    else
                    {
                        lastY = 0;
                    }
                }
            }
        }
        for (uint r = 0; r < _width; ++r)
        {
            for (uint c = 0; c < _width; ++c)
            {

                if (arr[r * _width + c] == VectorState::Continue)
                {
                    if (r == axis || c == axis)
                    {
                        cout << "\033[92m[•]\033[39m";
                    }
                    else
                    {
                        cout << "\033[91m[•]\033[39m";
                    }
                }
                else if (arr[r * _width + c] == VectorState::Intersection)
                {
                    cout << "\033[96m[•]\033[39m";
                }
                else if (arr[r * _width + c] == VectorState::Approximate)
                {
                    cout << "\033[31m[•]\033[39m";
                }
                else if (r == axis && c == axis)
                {
                    cout << "\033[97m━╋━\033[39m";
                }
                else if (r == axis)
                {
                    cout << "\033[97m━━━\033[39m";
                }
                else if (c == axis)
                {
                    cout << "\033[97m ┃ \033[39m";
                }
                else
                {
                    cout << "\033[90m[ ]\033[39m";
                }
            }
            cout << std::endl;
        }
        return arr;
    }
    template <invocable_result<double, double> Fn>
    VectorState *graph(int _width, double unit, Fn f, VectorState *arr)
    {
        assert(unit > 0);
        int quad = (int)(_width / 2) * unit;
        const int axis = std::ceil(_width / 2);
        int lastY = -1;
        int lastX = -1;
        bool lastExists = false;
        for (int j = -_width / 2; j <= _width / 2; ++j)
        {
            int y = std::round(f(j * unit) / unit);
            if (y <= quad && y >= -quad)
            {
                if (y < 0)
                {
                    y = std::abs(y) + _width / 2;
                }
                else
                {
                    y = std::abs(y - _width / 2);
                }
                if (lastY != -1)
                {
                    if (lastExists)
                    {
                        if (lastY > y)
                        {
                            for (int dy = 1; dy < lastY - y; ++dy)
                            {
                                arr[(dy + y) * _width + lastX + 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                        else if (lastY < y)
                        {
                            for (int dy = 1; dy < y - lastY; ++dy)
                            {
                                arr[(dy + lastY) * _width + lastX + _width / 2] = VectorState::Approximate;
                            }
                        }
                    }
                    else
                    {
                        int yCopy = std::round(f((j - 1) * unit + 0.000001) / unit);
                        if (yCopy < 0)
                        {
                            for (int dy = y + 1; dy < _width; ++dy)
                            {
                                arr[dy * _width + j - 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                        else
                        {
                            for (int dy = y - 1; dy >= 0; --dy)
                            {
                                arr[dy * _width + j - 1 + _width / 2] = VectorState::Approximate;
                            }
                        }
                    }
                }
                lastY = y;
                lastX = j;
                lastExists = true;
                lastY = y;
                auto &l = arr[y * _width + j + _width / 2];
                if (l == VectorState::Continue || l == VectorState::Approximate)
                {
                    l = VectorState::Intersection;
                    continue;
                }
                l = VectorState::Continue;
            }
            else
            {
                if (lastExists)
                {
                    lastExists = false;
                    y = std::round(f(j * unit - 0.000001) / unit);
                    if (y < 0)
                    {
                        for (int dy = lastY + 1; dy < _width; ++dy)
                        {
                            arr[dy * _width + j + _width / 2] = VectorState::Approximate;
                        }
                        lastY = _width;
                    }
                    else
                    {
                        for (int dy = lastY - 1; dy >= 0; --dy)
                        {
                            arr[dy * _width + j + _width / 2] = VectorState::Approximate;
                        }
                        lastY = 0;
                    }
                }
                else
                {
                    lastExists = false;
                    if (y < 0)
                    {
                        lastY = _width;
                    }
                    else
                    {
                        lastY = 0;
                    }
                }
            }
        }
        for (uint r = 0; r < _width; ++r)
        {
            for (uint c = 0; c < _width; ++c)
            {

                if (arr[r * _width + c] == VectorState::Continue)
                {
                    if (r == axis || c == axis)
                    {
                        cout << "\033[92m[•]\033[39m";
                    }
                    else
                    {
                        cout << "\033[91m[•]\033[39m";
                    }
                }
                else if (arr[r * _width + c] == VectorState::Intersection)
                {
                    cout << "\033[96m[•]\033[39m";
                }
                else if (arr[r * _width + c] == VectorState::Approximate)
                {
                    cout << "\033[31m[•]\033[39m";
                }
                else if (r == axis && c == axis)
                {
                    cout << "\033[97m━╋━\033[39m";
                }
                else if (r == axis)
                {
                    cout << "\033[97m━━━\033[39m";
                }
                else if (c == axis)
                {
                    cout << "\033[97m ┃ \033[39m";
                }
                else
                {
                    cout << "\033[90m[ ]\033[39m";
                }
            }
            cout << std::endl;
        }
        return arr;
    }

}

#endif