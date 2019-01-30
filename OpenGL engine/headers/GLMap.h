#define EDGE_SIZE 0.1f
#define MAP_RENDER_DISTANCE 16

struct PerlinIndex {
    int x;
    int y;
};

class Map {
    public:
        std::vector<int> arrayPerlin;
        std::vector<glm::vec3> objectPositions;
        PerlinIndex perlini;
        int width;

        Map();

        void loadPerlinImage(std::string path);  
        void cleanPerlinArray();
        void addObjectPosition(float x, float y, float z);
        int getPerlinIndex(float camPos, int axis);
};

