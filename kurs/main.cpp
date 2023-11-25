#include "document.h"

int main() {
    std::vector<std::shared_ptr<Document>> archive;
    init(archive);
    menu(archive);
}