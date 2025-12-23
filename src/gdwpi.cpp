#include "gdwpi.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <fmt/format.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/GenericEntry.h>

using namespace godot;

GDNetworkTable::GDNetworkTable() {}

GDNetworkTable::~GDNetworkTable() {}

void GDNetworkTable::_ready() {
    inst = nt::NetworkTableInstance::GetDefault();
    inst.SetServer("localhost");
    table = inst.GetTable("datatable");

    for(String name : entrylist) {
        CharString temp = name.utf8();
        std::string val = temp.get_data();
        entryMap[val] = table->GetTopic(val).GetGenericEntry();
    }

    inst.StartClient4("GDNetworkTable");
}

void GDNetworkTable::_bind_methods() {
    ClassDB::bind_method(D_METHOD("fetch_double", "name"), &GDNetworkTable::fetch_double);
    ClassDB::bind_method(D_METHOD("fetch_string", "name"), &GDNetworkTable::fetch_string);
    ClassDB::bind_method(D_METHOD("fetch_int", "name"), &GDNetworkTable::fetch_int);

    ClassDB::bind_method(D_METHOD("push_double", "name", "value"), &GDNetworkTable::push_double);
    ClassDB::bind_method(D_METHOD("push_string", "name", "value"), &GDNetworkTable::push_string);
    ClassDB::bind_method(D_METHOD("push_int", "name", "value"), &GDNetworkTable::push_int);

    ClassDB::bind_method(D_METHOD("get_entrylist"), &GDNetworkTable::get_entrylist);
    ClassDB::bind_method(D_METHOD("set_entrylist", "p_entrylist"), &GDNetworkTable::set_entrylist);

    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "entrylist", PROPERTY_HINT_TYPE_STRING, String::num(Variant::STRING) + ":"), "set_entrylist", "get_entrylist");


}

void GDNetworkTable::set_entrylist(Array p_entrylist) {
    entrylist = p_entrylist;
}

Array GDNetworkTable::get_entrylist() {
    return entrylist;
}

// currently only supports doubles, strings, and integers but NetworkTables has support for bools, floats, and arrays
// they were deemed not necessary but should not be difficult to implement if needed

double GDNetworkTable::fetch_double(String name) {
    if(entrylist.find(name) == -1) {
        print_line("Error: value not in list");
        return 0.0;
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();
    return (entryMap[val]).GetDouble(0.0);
}

String GDNetworkTable::fetch_string(String name) {
    if(entrylist.find(name) == -1) {
        print_line("Error: value not in list");
        return String("");
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();
    std::string result = (entryMap[val]).GetString("");
    return String(result.data());
}

int GDNetworkTable::fetch_int(String name) {
    if(entrylist.find(name) == -1) {
        print_line("Error: value not in list");
        return 0;
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();
    return (entryMap[val]).GetInteger(0);
}

// returns true on success
bool GDNetworkTable::push_double(String name, double value) {
    if(entrylist.find(name) == -1) {
        print_line(name);
        print_line("Error: value not in list");
        return false;
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();
    return entryMap[val].SetDouble(value);
}

bool GDNetworkTable::push_string(String name, String value) {
    if(entrylist.find(name) == -1) {
        print_line(name);
        print_line("Error: value not in list");
        return false;
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();

    CharString temp2 = value.utf8();
    std::string val2 = temp2.get_data();
    return entryMap[val].SetString(val2);
}

bool GDNetworkTable::push_int(String name, int value) {
    if(entrylist.find(name) == -1) {
        print_line(name);
        print_line("Error: value not in list");
        return false;
    }
    CharString temp = name.utf8();
    std::string val = temp.get_data();
    return entryMap[val].SetInteger(value);
}
