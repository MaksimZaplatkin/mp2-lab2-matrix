// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size is too large");
        }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(sz, v.sz);
        swap(pMem, v.pMem);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
        {
            return *this;
        }

        sz = v.sz;
        delete[] pMem;

        pMem = new T[sz];
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
        {
            swap(sz, v.sz);
            swap(pMem, v.pMem);
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        return at(ind);
    }
    const T& operator[](size_t ind) const
    {
        return at(ind);
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind<0 || ind>sz - 1)
        {
            throw out_of_range("Index error");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind<0 || ind>sz - 1)
        {
            throw out_of_range("Index error");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) {
            return false;
        }

        for (int i = 0; i < v.sz; i++)
        {
            if (this->pMem[i] != v.pMem[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] + val;
        }
        return res;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (v.sz != sz)
        {
            throw length_error("dif sizes");
        }
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (v.sz != sz)
        {
            throw length_error("dif sizes");
        }
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (v.sz != sz)
        {
            throw length_error("dif sizes");
        }
        T result = 0;
        for (int i = 0; i < sz; i++) {
            result += pMem[i] * v.pMem[i];
        }
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s <= 0 || s > MAX_MATRIX_SIZE)
        {
            throw out_of_range("Range Error");
        }
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        //if (m.sz != sz)
        //{
        //    return false;
        //}
        //for (int i = 0; i < sz; i++)
        //{
        //    if (pMem[i] != m.pMem[i])
        //    {
        //        return false;
        //    }
        //}
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] * val;
        }
        return result;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw out_of_range("Size error");

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] * v;
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        //if (sz != m.sz)
        //    throw out_of_range("dif sizes");

        //TDynamicMatrix<T> result(sz);
        //for (size_t i = 0; i < sz; i++)
        //{
        //    result[i] = pMem[i] + m.pMem[i];
        //}
        return TDynamicMatrix(*this + m);
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        /*if (sz != m.sz)
            throw out_of_range("dif sizes");

        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] - m.pMem[i];
        }*/
        return TDynamicMatrix(*this - m);
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        /*if (sz != m.sz)
            throw out_of_range("dif sizes");

        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                result[i][j] = T();
                for (size_t k = 0; k < sz; k++)
                {
                    result[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }*/
        return TDynamicMatrix(*this * m);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n';
        return ostr;
    }
};

#endif
