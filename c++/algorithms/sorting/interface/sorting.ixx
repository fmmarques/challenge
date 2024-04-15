module ;

#include <memory>

export module sorting;

export {
    namespace functional {
        namespace v1_0_0_0 {

            template < typename T > struct immutable {
                immutable(const immutable< T >&) = default;
                immutable(immutable< T >&&) = default;
                immutable& operator=(const immutable< T >&) = default;
                immutable& operator=(immutable< T >&) = default;

                operator T& () const& { return _v; }
                const T& operator*() const& { return _v; }
                const T* operator->() const& { return std::addressof(_v); }
            private:
                T _v;
            };
        }
    }
}
