#include <iostream>
#include <vector>
#include <fstream>

// total number
unsigned int materials_in_stock;
// number of materials that got borrowed
unsigned int materials_borrowed;
std::ifstream ifs;
std::ofstream ofs;

class materials
{
    public:
        materials();
        materials(std::string id, std::string type, std::string name, std::string author, bool state, std::string b_id, unsigned int year, unsigned int month, unsigned int day);
        ~materials();
        // id
        void set_id(std::string id);
        std::string get_id() const;
        // type
        void set_type(std::string type);
        std::string get_type() const;
        // name
        std::string get_name() const;
        void set_name(std::string name);
        // author
        std::string get_author() const;
        void set_author(std::string author);
        // is_in_stock
        bool get_state() const;
        void set_state(bool b);
        // b_id (borrower's id)
        std::string get_b_id() const;
        void set_b_id(std::string id);
        // year
        unsigned int get_year() const;
        void set_year(unsigned int year);
        // month
        unsigned int get_month() const;
        void set_month(unsigned int month);
        // day
        unsigned int get_day() const;
        void set_day(unsigned int day);
        // p_next
        materials *get_next() const;
        void set_next(materials *p_next);
        // print
        void print() const;

    private:
        std::string m_name;
        std::string m_author;
        bool m_state;
        std::string m_id;
        std::string m_type;
        // borrower's id
        std::string m_b_id;
        // expected return date for materials
        unsigned int m_expReturnYear;
        unsigned int m_expReturnMonth;
        unsigned int m_expReturnDay;
        materials *p_next;
};

class materials_list
{
    public:
        materials_list();
        ~materials_list();
        materials *get_p_head() const;
        void set_p_head(materials *p);
        bool not_nullptr() const;
        // get id of the temporary holder (borrower) of a material
        materials *get_b_id(std::string m) const;

    private:
        materials *p_head;
};
