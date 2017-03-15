#ifndef THESIS_MAPUTILS_H
#define THESIS_MAPUTILS_H

namespace map_utils{
    struct GetKeys {
        template <typename T>
        typename T::first_type operator()(T keyValuePair) const {
            return keyValuePair.first;
        }
    };

    struct GetValues {
        template <typename T>
        typename T::first_type operator()(T keyValuePair) const {
            return keyValuePair.second;
        }
    };
}

#endif 
