#if !defined CPP_SORTING
#	define CPP_SORTING

export module sorting;
import <type_traits>;


export {
	/* Exports by the sorting module. */
    namespace v1_0_0_0 
    {
        template < typename T > concept partially_orderable = std::is_scalar_v< T >;
        
        template < typename T > concept completely_orderable = std::is_scalar_v< T >;
        
        template < typename T > concept orderable = partially_orderable< T > || completely_orderable< T >;
        
        template < class C, typename T = C::value_type > concept orderable_container = orderable< T >;
        
        template < orderable_container C >
        immutable<C> mergesort(immutable<C>& arr, uint32_t l, uint32_t r) {
            auto const merge = [](C& arr, uint32_t l, uint32_t m, uint32_t r) {
                uint32_t i, j, k;
                uint32_t n1 = m - l + 1;
                uint32_t n2 = r - m;
                
                C L(n1), R(n2);
                
                for (i = 0; i < n1; i++)
                    L[i] = arr[l + i];
                for (j = 0; j < n2; j++)
                    R[j] = arr[m + 1 + j];
                    
                i = 0;
                j = 0;
                k = l;
                while (i < n1 && j < n2) {
                    if (L[i] <= R[j]) {
                        arr[k] = L[i];
                        i++;
                    }
                    else {
                        arr[k] = R[j];
                        j++;
                    }
                    k++;
                }
                
                while (i < n1) {
                    arr[k] = L[i];
                    i++;
                    k++;
                }
                
                while (j < n2) {
                    arr[k] = R[j];
                    j++;
                    k++;
                }
                };
                
                
            if (l < r) {
                int m = l + (r - l) / 2;
                
                mergeSort(arr, l, m);
                mergeSort(arr, m + 1, r);
                
                merge(arr, l, m, r);
            }
        }
    }
    namespace sorting = sorting_implementations::v1_0_0_0;
}

#endif