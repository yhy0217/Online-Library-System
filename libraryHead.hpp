#include <iostream>
#include <vector>
#include <fstream>
#include "materialHead.hpp"

class library
{
    public:
        library();
        ~library();
        // functions accessible to all users
        // search materials - by materials' ids
        materials *search_by_id(std::string id);
        // search materials - by materials' names
        materials *search_by_name(std::string name);
        // search materials - by borrowers' ids
        materials *search_by_b_id(std::string id);
        void print_all_materials();
        void set_state_list_borrow(materials *m);
        void set_state_list_return(materials *m);
        unsigned int get_user_num();
        void add_new_user(std::string id);
        bool user_exists(std::string id);

    protected:
        materials_list m_l;

    private:
        std::vector<std::string> u_list;
        unsigned int user_num;
};

class borrower : public library
{
    public:
        void borrow_book(materials *m);
        void return_book(materials *m);
        virtual bool reach_max() = 0;
        void borrowed_list();
        std::string get_name();

    protected:
        std::string b_name;
        std::string b_id;
        unsigned int b_num_borrowed;
};

class student : public borrower
{
    public:
        student(std::string name, unsigned int identity);
        ~student();
        virtual bool reach_max();

    private:
        bool max;
};

class staff : public borrower
{
    public:
        staff(std::string name, unsigned int identity);
        ~staff();
        virtual bool reach_max();

    private:
        bool max; 
};

class admin : public library
{
    public:
        admin();
        ~admin();
        bool is_admin(std::string id, std::string password);
        // functions that are open to admin only
        // add new material at the end of the materials list
        void insert(materials *new_m);
        // remove material from the library by id
        void removeId(std::string id);

    private:
        unsigned int user_num;
        std::string a_id;
        std::string a_password;
};
