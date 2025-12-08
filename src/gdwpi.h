#ifndef GDWPI
#define GDWPI

#include <godot_cpp/classes/node.hpp>
#include <networktables/GenericEntry.h>

#include <networktables/NetworkTableInstance.h>

namespace godot {


class GDNetworkTable : public Node {
    GDCLASS(GDNetworkTable, Node)

public:
    GDNetworkTable();
    ~GDNetworkTable();

    void _ready() override;
    //void _process(double delta) override;

    void set_entrylist(Array p_entrylist);
    Array get_entrylist();

    double fetch_double(String name);
    int fetch_int(String name);
    String fetch_string(String name);

    bool push_double(String name, double value);
    bool push_string(String name, String value);
    bool push_int(String name, int value);

private:
    nt::NetworkTableInstance inst;
    std::shared_ptr<nt::NetworkTable> table;
    std::map<std::string, nt::GenericEntry> entryMap;

    Array entrylist;

    Dictionary* get_values();
    void set_values(const Dictionary requested_values);

protected:
    static void _bind_methods();

};
}

#endif
