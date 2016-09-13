struct PointHasher {
    std::size_t operator()(const Point &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.getX()) + hash<int>()(k.getY());
    }
};


