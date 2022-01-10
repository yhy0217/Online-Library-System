#include "libraryHead.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#pragma once

library::library()
{
    // Open external file
    m_l.set_p_head(new materials);
    std::ifstream ifs_temp;
    ifs_temp.open("materials list.txt", std::ios::in);
    // Check if external file is empty
    char c = '\0';
    // If empty
    if ((ifs_temp >> c).eof())
    {
        std::cout << "no material information" << std::endl;
        ifs_temp.close();
    }
    // If not empty
    else
    {
        ifs.open("materials list.txt", std::ios::in);
        // buffer: used to store information temporarily 
        std::string buffer;
        // p_curr: a pointer used to iterate through the material list
        materials * p_curr = m_l.get_p_head(); 
        // count: used to match the read information with variables in the material nodes
        unsigned int count{0};
        // Initialize a linked list with information read from the external file
        while (std::getline(ifs, buffer, ' '))
        {
            if (buffer == std::to_string(EOF))
            {
                p_curr->set_next(nullptr);
                delete p_curr;
                p_curr = nullptr;
                break;
            }
            else
            {
                switch (count)
                {
                case 0:
                {
                    p_curr->set_name(buffer);
                    break;
                }
                case 1:
                {
                    p_curr->set_author(buffer);
                    break;
                }
                case 2:
                {
                    p_curr->set_id(buffer);
                    break;
                }
                case 3:
                {
                    if (buffer == "1")
                    {
                        p_curr->set_state(true);
                    }
                    else
                    {
                        p_curr->set_state(false);
                    }
                    break;
                }
                case 4:
                {
                    p_curr->set_type(buffer);
                    break;
                }
                case 5:
                {
                    p_curr->set_b_id(buffer);
                    break;
                }
                case 6:
                {
                    p_curr->set_year(std::stoul(buffer));
                    break;
                }
                case 7:
                {
                    p_curr->set_month(std::stoul(buffer));
                    break;
                }
                case 8:
                {
                    p_curr->set_day(std::stoul(buffer));
                    break;
                }
                }
                ++count;
                if (ifs.peek() == '\n')
                {
                    p_curr->set_next(new materials);
                    p_curr = p_curr->get_next();
                    ifs.ignore('\n');
                    count = 0;
                }
            }
        }
        ifs.close();
    }

    // 读取user_list
    // // 需不需要先进行一次写入（写入的东西为空），保证创建好文件，以第一次使用时读取成功
    ofs.open("user list.txt", std::ios::out | std::ios::ate);
    ofs.close();
    ifs.open("user list.txt", std::ios::in);
    // 需要考虑文件为空的问题
    c = '\0';
    if ((ifs >> c).eof())
    {
        u_list.push_back("");
        std::cout << "no user info" << std::endl;
    }
    else
    {
        std::vector<std::string>::iterator i;
        std::string buffer;
        // iterate vector
        for (i = u_list.begin(); i != u_list.end(); ++i)
        {
            std::getline(ifs, buffer);
            *i = buffer;
        }
        // user_num 初始化
    }
    ifs.close();
}

library::~library()
{
}

// Search materials by id
materials *library::search_by_id(std::string id)
{
    // Check if list is empty
    if (m_l.not_nullptr())
    {
        // Iterate through (linked) material list
        materials *p_curr{m_l.get_p_head()};
        while (p_curr->get_id() != id)
        {
            p_curr = p_curr->get_next();
        }
        if (p_curr == nullptr)
        {
            std::cout << "no such material exists" << std::endl;
            return nullptr;
        }
        // Return a material if found
        return p_curr;
    }
}

// Search materials by name
// Share similar process with search_by_id
materials *library::search_by_name(std::string name)
{
    if (m_l.not_nullptr())
    {
        materials *p_curr{m_l.get_p_head()};
        while (p_curr->get_name() != name)
        {
            p_curr = p_curr->get_next();
        }
        if (p_curr == nullptr)
        {
            std::cout << "no such material exists" << std::endl;
            return nullptr;
        }
        return p_curr;
    }
}

// Search for all materials borrowed by a user, through borrower's id
materials *library::search_by_b_id(std::string id)
{
    // Check if material list is empty
    if (m_l.not_nullptr())
    {
        // Initialize a linked list
        materials *new_list_head = new materials;
        materials *new_list_moving{new_list_head};
        materials *p_moving{m_l.get_p_head()};
        materials *p_temp = nullptr;
        // Iterate through the list 
        while (p_moving != nullptr)
        {
            // Add materials to the list if the recorded borrower's id matches
            if (p_moving->get_b_id() == id)
            {
                new_list_moving->set_next(p_moving);
            }
            p_moving = p_moving->get_next();
        }
        // Return the new list
        return new_list_head;
    }
    else
    {
        std::cout << "The book list is empty" << std::endl;
        return;
    }
}

// Output all materials in the library and their revelant information to the console
void library::print_all_materials()
{
    if (m_l.not_nullptr())
    {
        materials *p_curr = nullptr;
        for (p_curr = m_l.get_p_head(); p_curr != nullptr; p_curr = p_curr->get_next())
        {
            p_curr->print();
        }
        delete p_curr;
        p_curr = nullptr;
    }
}

// Set materials to "borrowed" state when borrowed
void library::set_state_list_borrow(materials *m)
{
    if (!m_l.not_nullptr() || m == nullptr)
    {
        return;
    }
    else
    {
        // Search for material by id
        // Returned pointer stored in p
        materials *p = search_by_id(m->get_id());
        if (p != nullptr)
        {
            // Update state in linked list
            p->set_state(false);
            // Synchronize the text file with the current state in linked list
            ofs.open("material list.txt", std::ios::out | std::ios::trunc);
            for (materials *p_curr{m_l.get_p_head()}; p_curr != nullptr; p_curr = p_curr->get_next())
            {
                ofs << p_curr->get_name() << ' ';
                ofs << p_curr->get_author() << ' ';
                ofs << p_curr->get_state() << ' ';
                ofs << p_curr->get_id() << ' ';
                if (!p_curr->get_state())
                {
                    ofs << p_curr->get_b_id() << ' ';
                    ofs << p_curr->get_year() << ' ';
                    ofs << p_curr->get_month() << ' ';
                    if (p_curr->get_next() == nullptr)
                    {
                        ofs << p_curr->get_day() << '\n';
                    }
                    else
                    {
                        ofs << p_curr->get_day() << ' \n';
                    }
                }
                else
                {
                    if (p_curr->get_next() == nullptr)
                    {
                        ofs << p_curr->get_type() << ' \n';
                    }
                    else
                    {
                        ofs << p_curr->get_type() << '\n';
                    }
                }
            }
            ofs.close();
        }
    }
}

// Set materials to "returned" state when returned
// Share similar process with set_state_list_borrow
void library::set_state_list_return(materials *m)
{
    if (!m_l.not_nullptr() || m == nullptr)
    {
        return;
    }
    else
    {
        materials *p = search_by_id(m->get_id());
        if (p != nullptr)
        {
            p->set_state(true);
            ofs.open("material list.txt", std::ios::out | std::ios::trunc);
            for (materials *p_curr{m_l.get_p_head()}; p_curr != nullptr; p_curr = p_curr->get_next())
            {
                ofs << p_curr->get_name() << ' ';
                ofs << p_curr->get_author() << ' ';
                ofs << p_curr->get_state() << ' ';
                ofs << p_curr->get_id() << ' ';
                ofs << p_curr->get_type() << ' ';
                if (!p_curr->get_state())
                {
                    ofs << p_curr->get_b_id() << ' ';
                    ofs << p_curr->get_year() << ' ';
                    ofs << p_curr->get_month() << ' ';
                    ofs << p_curr->get_day() << '\n';
                }
            }
            ofs.close();
        }
    }
}

unsigned int library::get_user_num()
{
    return user_num;
}

void library::add_new_user(std::string id)
{
    // Push a new user to the end of the user list vector
    u_list.push_back(id);
    // Synchronize the text file with the current information in vector
    ofs.open("user list.txt", std::ios::out | std::ios::ate);
    ofs << id << "\n";
    ofs.close();
    // Increment number of users for future id generation
    ++user_num;
}

// Check if a user has signed up using id
bool library::user_exists(std::string id)
{
    ifs.open("user list.txt", std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << "no user list exists" << std::endl;
        return false;
    }
    std::string buffer;
    while (std::getline(ifs, buffer))
    {
        // If a user with the same id is found, return true,
        // otherwise, return false
        if (buffer == id)
        {
            return true;
        }
    }
    return false;
}

// class borrower
// Functions accessible to students and staff
void borrower::borrow_book(materials *m)
{
    // ???????????????????????????
    if (reach_max())
    {
        std::cout << "reach maximum" << std::endl;
        return;
    }
    set_state_list_borrow(m);
    ++b_num_borrowed;
}

void borrower::return_book(materials *m)
{
    set_state_list_return(m);
    --b_num_borrowed;
}

// Output a user's list of borrowed materials to the console
void borrower::borrowed_list()
{
    materials *p_curr{search_by_b_id(b_id)};
    // If list is not empty
    // Iterate and print all entries to the console
    while (p_curr != nullptr)
    {
        p_curr->print();
        p_curr = p_curr->get_next();
    }
    // Deallocate memory
    delete p_curr;
    p_curr = nullptr;
}

std::string borrower::get_name()
{
    return b_name;
}

// class student
// Initialize new student objects with user input
student::student(std::string name, unsigned int identity)
{
    b_name = name;
    b_num_borrowed = 0;
    b_id = "S" + std::to_string(get_user_num());
    add_new_user(b_id);
}

student::~student()
{
}

// Determine if a student has borrowed more materials (>3) than allowed
bool student::reach_max()
{
    if (b_num_borrowed == 3)
    {
        return true;
    }
    return false;
}

// class staff
// Initialize new staff objects with user input
staff::staff(std::string name, unsigned int identity)
{
    b_name = name;
    b_num_borrowed = 0;
    b_id = "T" + std::to_string(get_user_num());
    add_new_user(b_id);
}

staff::~staff()
{
}

// Determine if a staff has borrowed more materials (>5) than allowed
bool staff::reach_max()
{
    if (b_num_borrowed >= 5)
    {
        return true;
    }
    return false;
}

// class admin
admin::admin()
{
    // set admin login credentials
    a_id = "Admin";
    a_password = "dhiusousou12123";
}

admin::~admin()
{
}

bool admin::is_admin(std::string id, std::string password)
{
    if ((id == a_id) && (password == a_password))
    {
        return true;
    }
    return false;
}

// Manually add new materials into the library
void admin::insert(materials *new_m)
{
    materials *p_head = m_l.get_p_head();
    // If material list is empty,
    // initialize a new linked list with the new material as the first node
    if (p_head == nullptr)
    {
        p_head = new_m;
        new_m->set_next(nullptr);
    }
    // Else, add new material to the end of the original list
    else
    {
        materials *p_moving = m_l.get_p_head();
        while (p_moving->get_next() != nullptr)
        {
            p_moving = p_moving->get_next();
        }
        p_moving->set_next(new_m);
        new_m->set_next(nullptr);
        delete p_moving;
        p_moving = nullptr;
    }

    // Synchronize the text file with the updated linked list
    ofs.open("material list.txt", std::ios::out | std::ios::ate);
    ofs << new_m->get_name() << ' ';
    ofs << new_m->get_author() << ' ';
    ofs << new_m->get_state() << ' ';
    ofs << new_m->get_id() << ' ';
    ofs << new_m->get_type() << ' ';
    if (!new_m->get_state())
    {
        ofs << new_m->get_b_id() << ' ';
        ofs << new_m->get_year() << ' ';
        ofs << new_m->get_month() << ' ';
        ofs << new_m->get_day() << '\n';
    }
    ofs.close();
}

// Manually remove a material from the library by id
void admin::removeId(std::string id)
{
    if (m_l.not_nullptr())
    {
        materials *p_moving = m_l.get_p_head();
        materials *p = search_by_id(id);
        if (p == nullptr)
        {
            std::cout << "no matched item" << std::endl;
            return;
        }
        // If found the material with matching id,
        // remove it from the (linked) material list
        else
        {
            if (p_moving->get_id() == id)
            {
                p_moving = p_moving->get_next();
                m_l.set_p_head(p_moving);
            }
            else
            {
                while (p_moving->get_next() != p)
                {
                    p_moving = p_moving->get_next();
                }
                materials *p_last = p_moving;
                p_moving = p_moving->get_next();
                p_last->set_next(p_moving->get_next());
                p_moving->set_next(nullptr);
                delete p_moving;
                p_moving = nullptr;
            }
            // Synchronize the text file with the current linked list
            ofs.open("material list.txt", std::ios::out | std::ios::trunc);
            for (materials *p_curr{m_l.get_p_head()}; p_curr != nullptr; p_curr = p_curr->get_next())
            {
                ofs << p_curr->get_name() << ' ';
                ofs << p_curr->get_author() << ' ';
                ofs << p_curr->get_state() << ' ';
                ofs << p_curr->get_id() << ' ';
                ofs << p_curr->get_type() << ' ';
                if (!p_curr->get_state())
                {
                    ofs << p_curr->get_b_id() << ' ';
                    ofs << p_curr->get_year() << ' ';
                    ofs << p_curr->get_month() << ' ';
                    ofs << p_curr->get_day() << '\n';
                }
            }
            ofs.close();
        }
    }
    else
    {
        std::cout << "the file is empty" << std::endl;
    }
}
