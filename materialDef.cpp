#include "materialHead.hpp"
#include "libraryDef.cpp"
#include <iostream>
#include <fstream>
#include <algorithm>

// class materials
// Declared class for books and CDs in library

// Default initialization
materials::materials()
{
    this->m_name = "New Book";
    this->m_author = "Author";
    this->m_state = false;
    this->m_id = 1;
    this->m_type = "Type";
    this->m_b_id = "";
    this->m_expReturnYear = 1900;
    this->m_expReturnMonth = 1;
    this->m_expReturnDay = 1;
    this->p_next = nullptr;
}

// Initialization with admin input
materials::materials(std::string id, std::string type, std::string name, std::string author, bool state, std::string b_id, unsigned int year, unsigned int month, unsigned int day)
{
    this->m_name = name;
    this->m_author = author;
    this->m_state = state;
    this->m_id = id;
    this->m_type = type;
    this->m_b_id = b_id;
    this->m_expReturnYear = 1900;
    this->m_expReturnMonth = 1;
    this->m_expReturnDay = 1;
    this->p_next = nullptr;
}

materials::~materials()
{
}

std::string materials::get_id() const { return m_id; }
void materials::set_id(std::string id) { this->m_id = id; }

std::string materials::get_type() const { return m_type; }
void materials::set_type(std::string type) { this->m_type = type; }

std::string materials::get_name() const { return m_name; }
void materials::set_name(std::string name) { this->m_name = name; }

std::string materials::get_author() const { return m_author; }
void materials::set_author(std::string author) { this->m_author = author; };

bool materials::get_state() const { return m_state; }
void materials::set_state(bool b) { this->m_state = b; };

std::string materials::get_b_id() const { return m_b_id; }
void materials::set_b_id(std::string id) { this->m_b_id = id; }

unsigned int materials::get_year() const { return m_expReturnYear; }
void materials::set_year(unsigned int year) { this->m_expReturnYear = year; };

unsigned int materials::get_month() const { return m_expReturnMonth; }
void materials::set_month(unsigned int month) { this->m_expReturnMonth = month; };

unsigned int materials::get_day() const { return m_expReturnDay; }
void materials::set_day(unsigned int day) { this->m_expReturnDay = day; };

materials *materials::get_next() const { return this->p_next; }
void materials::set_next(materials *p_next) { this->p_next = p_next; };

// class material_list
// A linked list storing material objects as nodes
materials_list::materials_list()
{
    p_head = nullptr;
}

// Delete linked list and deallocate relevant pointers
materials_list::~materials_list()
{
    if (not_nullptr())
    {
        materials *p_curr{p_head};
        while (p_curr != nullptr)
        {
            materials *p_temp{p_curr};
            p_curr = p_curr->get_next();
            delete p_temp;
            p_temp = nullptr;
        }
        delete p_curr;
        p_curr = nullptr;
    }
}

materials *materials_list::get_p_head() const
{
    return p_head;
}

void materials_list::set_p_head(materials *p)
{
    p_head = p;
    return;
}

// Output material and relevant information to the console
void materials::print() const
{
    std::cout << "name: " << this->get_name() << "\t"
              << "id: " << this->get_id() << "\t"
              << "type: " << this->get_type() << "\t"
              << "author: " << this->get_author() << "\t";
    if (this->get_state())
    {
        std::cout << "state: in stock"
                  << "\t";
    }
    else
    {
        std::cout << "state: borrowed"
                  << "\t"
                  << "expected to be returned on: " << this->get_year() << "."
                  << this->get_month() << "."
                  << this->get_day() << std::endl;
    }
}

// Check if the list is empty
bool materials_list::not_nullptr() const
{
    if (p_head == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}