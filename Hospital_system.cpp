#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define ll long long
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

// Handling data types

struct Member // General info
{
    int Id;
    string name;
    bool Male = 1;
    int age;
};

const string YEAR = "2025";
struct Date
{
    string day;
    string month;
    string year = YEAR;
};

struct Patient;
struct Doctor
{
    Member personal_info;
    string doc_major;
    int years_of_Ex;
    double Sallary;
    deque<pair<Date, Patient>> schedule;
};

struct Nurse
{
    Member personal_info;
    int years_of_Ex;
    double Sallary;
    vector<Patient> cur_pa;
};
struct Patient
{
    Member personal_info;
    string blood_type;
    string dr_Major;
    Date admissionDate;
    Doctor dc;
    Nurse Nr;
};

struct Medicine
{
    int Id;
    string Name;
    int quantity;
    double price;
};

vector<Patient> Patient_list;
vector<Doctor> Doctor_list;
vector<Nurse> Nurse_list;
vector<string> Majors;
map<string, vector<Doctor>> av_maj;
vector<Medicine> Parmacy;
// General functions
double Sallary_generator(int Ex) // Gen sallary
{
    if (Ex <= 3)
    {
        return 20'700;
    }
    else if (Ex > 3 && Ex <= 5)
    {
        return 40'870;
    }
    else if (Ex > 5 && Ex <= 8)
    {
        return 70'800;
    }
    else if (Ex > 8 && Ex <= 10)
    {
        return 100'050;
    }

    return 150'100;
}

template <typename T> // tmplate to be more Dynamic
bool Nur_sort(T x, T y)
{
    return x.cur_pa.size() < y.cur_pa.size();
}

template <typename T>
bool sort_By_id(T x, T y)
{
    return x.personal_info.Id < y.personal_info.Id;
}

template <typename T>
bool sort_By_name(T x, T y)
{
    return x.personal_info.name < y.personal_info.name;
}

template <typename T>
bool sort_By_age(T x, T y)
{
    return x.personal_info.age < y.personal_info.age;
}

template <typename T>
bool sort_By_date(T x, T y)
{
    if (x.admissionDate.day != y.admissionDate.day)
        return x.admissionDate.day < y.admissionDate.day;

    if (x.admissionDate.month != y.admissionDate.month)
        return x.admissionDate.month < y.admissionDate.month;

    return x.admissionDate.year < y.admissionDate.year;
}

template <typename T>
bool sort_By_Ex(T x, T y)
{
    return x.years_of_Ex < y.years_of_Ex;
}

// essential Majors
void fill_Majors()
{
    Majors.resize(5);
    Majors[0] = "Cardiology";      // heart and circulatory system
    Majors[1] = "Neurology";       // brain and nervous system
    Majors[2] = "Orthopedics";     // bones, joints, and muscles
    Majors[3] = "Pediatrics";      // children's health
    Majors[4] = "General Surgery"; // surgical treatments
}
// essential Doctors
void fill_Doctors()
{
    Doctor_list.clear();

    // Cardiology
    Doctor_list.push_back({{1, "Ahmed Hassan", 1, 45}, "Cardiology", 12, (double)Sallary_generator(12)});
    Doctor_list.push_back({{2, "Mona Youssef", 0, 39}, "Cardiology", 7, (double)Sallary_generator(7)});
    av_maj["Cardiology"].push_back(Doctor_list[0]);
    av_maj["Cardiology"].push_back(Doctor_list[1]);

    // Neurology
    Doctor_list.push_back({{3, "Karim Ali", 1, 50}, "Neurology", 15, (double)Sallary_generator(15)});
    Doctor_list.push_back({{4, "Sara Ibrahim", 0, 42}, "Neurology", 9, (double)Sallary_generator(9)});
    av_maj["Neurology"].push_back(Doctor_list[2]);
    av_maj["Neurology"].push_back(Doctor_list[3]);

    // Orthopedics
    Doctor_list.push_back({{5, "Hany Mahmoud", 1, 47}, "Orthopedics", 10, (double)Sallary_generator(10)});
    Doctor_list.push_back({{6, "Layla Samir", 0, 38}, "Orthopedics", 6, (double)Sallary_generator(6)});
    av_maj["Orthopedics"].push_back(Doctor_list[4]);
    av_maj["Orthopedics"].push_back(Doctor_list[5]);

    // Pediatrics
    Doctor_list.push_back({{7, "Youssef Adel", 1, 35}, "Pediatrics", 4, (double)Sallary_generator(4)});
    Doctor_list.push_back({{8, "Mariam Nabil", 0, 40}, "Pediatrics", 11, (double)Sallary_generator(11)});
    av_maj["Pediatrics"].push_back(Doctor_list[6]);
    av_maj["Pediatrics"].push_back(Doctor_list[7]);

    // General Surgery
    Doctor_list.push_back({{9, "Tamer Said", 1, 52}, "General Surgery", 20, (double)Sallary_generator(20)});
    Doctor_list.push_back({{10, "Noha Fathy", 0, 44}, "General Surgery", 8, (double)Sallary_generator(8)});
    av_maj["General Surgery"].push_back(Doctor_list[8]);
    av_maj["General Surgery"].push_back(Doctor_list[9]);
}
// essenial Nurses
void fill_Nurses()
{
    Nurse_list.clear();

    vector<string> nurseNames = {
        "Sara Ali", "Omar Mahmoud", "Laila Hussein", "Mohamed Adel", "Hana Khaled",
        "Youssef Farid", "Mariam Nabil", "Khaled Samir", "Nourhan Mostafa", "Salma Tarek"};

    vector<int> nurseAges = {28, 35, 30, 40, 25, 32, 29, 38, 27, 33};
    vector<int> yearsExp = {3, 10, 5, 12, 2, 7, 4, 15, 6, 9};

    for (int i = 0; i < 10; i++)
    {
        Nurse n;
        n.personal_info.Id = 3000 + i;
        n.personal_info.name = nurseNames[i];
        n.personal_info.Male = (i % 2 == 1);
        n.personal_info.age = nurseAges[i];
        n.years_of_Ex = yearsExp[i];
        n.Sallary = Sallary_generator(n.years_of_Ex);
        Nurse_list.push_back(n);
    }
}
void fill_Pharmacy()
{
    Parmacy.clear();

    Parmacy.push_back({101, "Paracetamol", 100, 12.75});
    Parmacy.push_back({102, "Amoxicillin", 80, 25.50});
    Parmacy.push_back({103, "Ibuprofen", 120, 18.99});
    Parmacy.push_back({104, "Cough Syrup", 50, 30.25});
    Parmacy.push_back({105, "Vitamin C", 200, 10.45});
    Parmacy.push_back({106, "Aspirin", 150, 15.30});
    Parmacy.push_back({107, "Azithromycin", 60, 45.80});
    Parmacy.push_back({108, "Metformin", 90, 35.60});
    Parmacy.push_back({109, "Lisinopril", 70, 28.75});
    Parmacy.push_back({110, "Omeprazole", 110, 22.40});
    Parmacy.push_back({111, "Cetirizine", 130, 12.90});
    Parmacy.push_back({112, "Hydroxychloroquine", 40, 55.55});
    Parmacy.push_back({113, "Prednisone", 60, 32.20});
    Parmacy.push_back({114, "Clarithromycin", 50, 42.35});
    Parmacy.push_back({115, "Doxycycline", 75, 38.95});
    Parmacy.push_back({116, "Furosemide", 65, 20.15});
    Parmacy.push_back({117, "Atorvastatin", 85, 48.70});
    Parmacy.push_back({118, "Warfarin", 55, 52.45});
    Parmacy.push_back({119, "Losartan", 95, 40.85});
    Parmacy.push_back({120, "Insulin", 30, 75.99});
}

// Patient Management System features
// Add new patient
// Edit Exist Patient
// Print all patinets
void Add_New_Patient()
{

    Patient pt;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                        Add New Patient                     \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Put Patient's National ID : ";
    cin >> pt.personal_info.Id;

    bool found = 1;
    while (found)
    {
        found = 0;
        for (int i = 0; i < sz(Patient_list); i++)
        {
            if (pt.personal_info.Id == Patient_list[i].personal_info.Id)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            cout << "Patient with this ID already Exists!" << nl;
            cout << "put correct Patinet ID : " << nl;
            cin >> pt.personal_info.Id;
        }
    }

    //  name
    cin.ignore();
    cout << "Put patient's Name : ";
    getline(cin, pt.personal_info.name);

    // Age
    cout << "Put patent's Age : ";
    cin >> pt.personal_info.age;

    // Gender
    int gen;
    cout << "Male / Female" << nl;
    cout << "[1] Male" << nl;
    cout << "[2] Female" << nl;
    cout << "choose your Gender : ";
    cin >> gen;
    if (gen == 1)
        pt.personal_info.Male = 1;
    else
        pt.personal_info.Male = 0;

    // date;
    cout << "Date of the day ?" << nl;
    cout << "# Day : ";
    cin >> pt.admissionDate.day;
    cout << "# Month : ";
    cin >> pt.admissionDate.month;
    pt.admissionDate.year = YEAR;

    // Blood type
    cout << "Put Patient Blood Type : ";
    cin >> pt.blood_type;

    // choose major
    cout << "Available Majors : " << nl;
    for (int i = 0; i < sz(Majors); i++)
    {
        cout << i + 1 << " | " << Majors[i] << nl;
    }
    cout << "-------------------\n";
    int maj;
    cout << "Choose Major from [1 : " << sz(Majors) << "] : ";
    cin >> maj;
    pt.dr_Major = Majors[maj - 1];

    // choose doctor
    cout << "Available Doctors : " << nl;
    for (int i = 0; i < sz(av_maj[pt.dr_Major]); i++)
        cout << "[" << i + 1 << "] Dr. " << av_maj[pt.dr_Major][i].personal_info.name << nl;

    int doct;
    cout << "choose Your Doctor Now [1 : " << sz(av_maj[pt.dr_Major]) << "] : ";
    cin >> doct;
    int doctor_id = av_maj[pt.dr_Major][doct - 1].personal_info.Id; // to check wiht unique ting to avoid redunduncy of doctors name

    for (auto &c : Doctor_list)
    {
        if (doctor_id == c.personal_info.Id)
        {
            pt.dc = c;
            c.schedule.push_back({pt.admissionDate, pt});
            break;
        }
    }

    sort(Nurse_list.begin(), Nurse_list.end(), Nur_sort<Nurse>);
    pt.Nr = Nurse_list[0];

    Patient_list.push_back(pt);

    cout << "Patient added successfully!\n";
    cout << "-----------------------------\n";
    cout << "    Patient's Information    \n";
    cout << "-----------------------------\n";
    cout << "ID: " << pt.personal_info.Id << "\n";
    cout << "Name: " << pt.personal_info.name << "\n";
    cout << "Age: " << pt.personal_info.age << "\n";
    cout << "Gender: " << (pt.personal_info.Male ? "Male" : "Female") << "\n";
    cout << "Blood Type: " << pt.blood_type << "\n";
    cout << "Doctor's Major: " << pt.dr_Major << nl;
    cout << "Doctor's name: Dr. " << pt.dc.personal_info.name << nl;
    cout << "Admission Date: " << pt.admissionDate.day << "/"
         << pt.admissionDate.month << "/" << YEAR << "\n";
    cout << "-----------------------------\n";
}

void Edit_Patient()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                        Edit Patient                        \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int x;
    cout << "Search about Patient with Id : ";
    cin >> x;

    // search about this patinet
    bool found = 0, indx = -1;
    while (!found)
    {
        for (int i = 0; i < sz(Patient_list); i++)
        {
            if (x == Patient_list[i].personal_info.Id)
            {
                found = 1, indx = i;
                break;
            }
        }

        if (!found)
        {
            cout << "This Id doesn't Exsist!" << nl;
            cout << "please put Correct Id : ";
            cin >> x;
        }
    }

    // show patient list
    Patient pt = Patient_list[indx];
    cout << "-----------------------------\n";
    cout << "    Patient's Information    \n";
    cout << "-----------------------------\n";
    cout << "ID: " << pt.personal_info.Id << "\n";
    cout << "Name: " << pt.personal_info.name << "\n";
    cout << "Age: " << pt.personal_info.age << "\n";
    cout << "Gender: " << (pt.personal_info.Male ? "Male" : "Female") << "\n";
    cout << "Blood Type: " << pt.blood_type << "\n";
    cout << "Doctor's Major: " << pt.dr_Major << nl;
    cout << "Doctor's name: Dr. " << pt.dc.personal_info.name << nl;
    cout << "Admission Date: " << pt.admissionDate.day << "/"
         << pt.admissionDate.month << "/" << pt.admissionDate.year << "\n";
    cout << "-----------------------------\n";

    // what do you will change
    int nu;
    while (nu != 7)
    {
        cout << "What do you want to Edit ?" << nl;
        cout << "[1] Patient Name\n";
        cout << "[2] Age\n";
        cout << "[3] Blood Type\n";
        cout << "[4] Addmission Date\n";
        cout << "[5] Doctor's Major\n";
        cout << "[6] Doctor\n";
        cout << "[7] Finish\n";
        cout << "Choose Number from [1 : 7] : ";
        cin >> nu;
        bool cancel = 0;
        if (nu == 1) // name
        {
            string s;
            cout << "put a new name here : ";
            cin >> s;
            pt.personal_info.name = s;
            cout << "Patient's name is updated now!\n";
        }
        else if (nu == 2) // age
        {
            int ag;
            cout << "put a new age : ";
            cin >> ag;
            pt.personal_info.age = ag;
            cout << "Patient's age is updated now!\n";
        }
        else if (nu == 3) // blood type
        {
            string type;
            cout << "put a correct blood type : ";
            cin >> type;
            pt.blood_type = type;
            cout << "Patient's Blood is updated now!\n";
        }
        else if (nu == 4) // date
        {
            cout << "Date of the day ?" << nl;
            cout << "# Day : ";
            cin >> pt.admissionDate.day;
            cout << "# Month : ";
            cin >> pt.admissionDate.month;
            pt.admissionDate.year = YEAR;
            cout << "Date is updated now!\n";
        }
        else if (nu == 5) // major
        {
            cout << "Available Majors : " << nl;
            for (int i = 0; i < sz(Majors); i++)
            {
                cout << i + 1 << " | " << Majors[i] << nl;
            }
            cout << "-------------------\n";
            int maj;
            cout << "Choose Major from [1 : " << sz(Majors) << "] : ";
            cin >> maj;
            pt.dr_Major = Majors[maj - 1];
            cout << "Patient's Doctor Major is updated now!\n";
        }
        else if (nu == 6) // doctor
        {
            int last_doctor_id = pt.dc.personal_info.Id;
            cout << "Available Doctors : " << nl;
            for (int i = 0; i < sz(av_maj[pt.dr_Major]); i++)
                cout << "[" << i + 1 << "] Dr. " << av_maj[pt.dr_Major][i].personal_info.name << nl;

            int doct;
            cout << "choose Your Doctor Now [1 : " << sz(av_maj[pt.dr_Major]) << "] : ";
            cin >> doct;
            int doctor_id = av_maj[pt.dr_Major][doct - 1].personal_info.Id; // to check wiht unique key to avoid redunduncy of doctors name

            for (auto &c : Doctor_list)
            {
                if (doctor_id == c.personal_info.Id)
                {
                    pt.dc = c;
                    c.schedule.push_back({pt.admissionDate, pt});
                    break;
                }
            }

            for (int i = 0; i < sz(Doctor_list); i++)
            {
                bool found = 0;
                if (last_doctor_id == Doctor_list[i].personal_info.Id)
                {
                    for (int j = 0; j < sz(Doctor_list[i].schedule); j++)
                    {
                        if (Doctor_list[i].schedule[j].second.personal_info.Id == pt.personal_info.Id)
                        {
                            Doctor_list[i].schedule.erase(Doctor_list[i].schedule.begin() + j);
                            found = 1;
                            break;
                        }
                    }
                }
                if (found)
                    break;
            }

            cout << "Patient's Doctor is Changed now!\n";
        }
    }

    cout << "---------------------------------\n";
    cout << "   Updated Patient Information   \n";
    cout << "---------------------------------\n";
    cout << "ID: " << pt.personal_info.Id << "\n";
    cout << "Name: " << pt.personal_info.name << "\n";
    cout << "Age: " << pt.personal_info.age << "\n";
    cout << "Gender: " << (pt.personal_info.Male ? "Male" : "Female") << "\n";
    cout << "Blood Type: " << pt.blood_type << "\n";
    cout << "Doctor's Major: " << pt.dr_Major << nl;
    cout << "Doctor's name: Dr. " << pt.dc.personal_info.name << nl;
    cout << "Admission Date: " << pt.admissionDate.day << "/"
         << pt.admissionDate.month << "/" << pt.admissionDate.year << "\n";
    cout << "---------------------------------\n";
}

void Print_all_patients()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                      Show All Patients                     \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    if (Patient_list.empty())
    {
        cout << "No patients available.\n";
        return;
    }
    cout << "How would you like to sort the patients?" << nl;
    cout << "[1] By ID" << nl;
    cout << "[2] By Name" << nl;
    cout << "[3] By Age" << nl;
    cout << "[4] By Date" << nl;
    int cho;
    cout << "Choose an option [1-4]: ";
    cin >> cho;
    if (cho == 1)
    {
        sort(all(Patient_list), sort_By_id<Patient>);
    }
    else if (cho == 2)
    {
        sort(all(Patient_list), sort_By_name<Patient>);
    }
    else if (cho == 3)
    {
        sort(all(Patient_list), sort_By_age<Patient>);
    }
    else
    {
        sort(all(Patient_list), sort_By_date<Patient>);
    }

    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
    cout << "                                  List of All Patients                                        \n";
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";

    cout << left << setw(8) << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(5) << "Age"
         << " | " << setw(6) << "Gender"
         << " | " << setw(6) << "Blood"
         << " | " << setw(20) << "Doctor"
         << nl;

    cout << string(75, '-') << nl;

    for (auto &pt : Patient_list)
    {
        cout << left << setw(8) << pt.personal_info.Id
             << " | " << setw(20) << pt.personal_info.name
             << " | " << setw(5) << pt.personal_info.age
             << " | " << setw(6) << (pt.personal_info.Male ? "Male" : "Female")
             << " | " << setw(6) << pt.blood_type
             << " | " << setw(20) << pt.dc.personal_info.name
             << nl;
    }

    cout << string(75, '-') << nl;
    cout << "Total Patients: " << Patient_list.size() << nl;
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
}

//---------------------//

// Doctor Management System features
// Add New Doctor
// Edit Doctor
// Show all Doctors
// Show Doctor's list

void Add_Doctor()
{
    Doctor doc;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                        Add New Doctor                     \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Put Doctor's National ID : ";
    cin >> doc.personal_info.Id;

    bool found = 1;
    while (found) // check if Exist
    {
        found = 0;
        int x = doc.personal_info.Id;
        for (int i = 0; i < sz(Doctor_list); i++)
        {
            int y = Doctor_list[i].personal_info.Id;
            if (x == y)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            cout << "This ID is Exist!" << nl;
            cout << "Put Valid New ID : ";
            cin >> doc.personal_info.Id;
        }
    }

    // put All personal information
    cin.ignore();
    cout << "Valid ID" << nl;
    cout << "Put Doctor's Name : ";
    getline(cin, doc.personal_info.name);

    cout << "Put Doctor's Age : ";
    cin >> doc.personal_info.age;

    // gender
    int gen;
    cout << "Male / Female" << nl;
    cout << "[1] Male" << nl;
    cout << "[2] Female" << nl;
    cout << "choose your Gender : ";
    cin >> gen;
    if (gen == 1)
        doc.personal_info.Male = 1;
    else
        doc.personal_info.Male = 0;

    // years of Ex
    cout << "How Many years of your Experience? : ";
    cin >> doc.years_of_Ex;

    // Sallary
    doc.Sallary = (double)Sallary_generator(doc.years_of_Ex);

    // Major of Doctor
    cout << "Available Majors : " << nl;
    for (int i = 0; i < sz(Majors); i++)
    {
        cout << i + 1 << " | " << Majors[i] << nl;
    }
    cout << sz(Majors) + 1 << " | " << "Another major" << nl;
    cout << "-------------------\n";
    int maj;
    cout << "What is your Major ? ";
    cin >> maj;
    if (maj == sz(Majors) + 1)
    {
        string new_maj;
        cout << "Put Your Major : ";
        cin >> new_maj;
        Majors.push_back(new_maj);
        av_maj[new_maj] = {};
        doc.doc_major = new_maj;
    }
    else
    {
        doc.doc_major = Majors[maj - 1];
    }

    Doctor_list.push_back(doc);           // add doctor to list
    av_maj[doc.doc_major].push_back(doc); // add doctor to av_maj

    cout << "Doctor added successfully!\n";
    cout << "-----------------------------\n";
    cout << "     Doctor's Information    \n";
    cout << "-----------------------------\n";
    cout << "Doctor's ID : " << doc.personal_info.Id << nl;
    cout << "Doctor's Name : " << doc.personal_info.name << nl;
    cout << "Doctor's Age : " << doc.personal_info.age << nl;
    cout << "Doctor's Gender : " << (doc.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years of Ex : " << doc.years_of_Ex << nl;
    cout << "Doctor's Major : " << doc.doc_major << nl;
    cout << "Doctor's Sallary : " << doc.Sallary << nl;
    cout << "-----------------------------\n";
}

void Edit_Doctor()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                        Edit Doctor                         \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int x;
    cout << "Search about Doctor with Id : ";
    cin >> x;

    bool found = 0;
    int indx = -1;
    while (!found)
    {

        for (int i = 0; i < sz(Doctor_list); i++)
        {
            int y = Doctor_list[i].personal_info.Id;
            if (x == y)
            {
                found = 1, indx = i;
                break;
            }
        }

        if (!found)
        {
            cout << "This ID Not Exist!" << nl;
            cout << "please put correct ID : ";
            cin >> x;
        }
    }

    Doctor doc = Doctor_list[indx];
    cout << "-------------------------------\n";
    cout << "      Current information      \n";
    cout << "-------------------------------\n";
    cout << "Doctor's ID : " << doc.personal_info.Id << nl;
    cout << "Doctor's Name : " << doc.personal_info.name << nl;
    cout << "Doctor's Age : " << doc.personal_info.age << nl;
    cout << "Doctor's Gender : " << (doc.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years of Ex : " << doc.years_of_Ex << nl;
    cout << "Doctor's Major : " << doc.doc_major << nl;
    cout << "Doctor's Sallary : " << doc.Sallary << nl;
    cout << "-------------------------------\n";

    int cho;

    while (cho != 5)
    {
        cout << "Chose what do you want to change\n";
        cout << "[1] Name\n";
        cout << "[2] Age\n";
        cout << "[3] Years of Experience\n";
        cout << "[4] Major\n";
        cout << "[5] Finish\n";
        cout << "put your Choise : ";
        cin >> cho;
        if (cho == 1)
        {
            string s;
            cin.ignore();
            cout << "put your New Name : ";
            getline(cin, s);
            doc.personal_info.name = s;
            cout << "Your name was edited successfully.\n";
        }
        else if (cho == 2)
        {
            int a;
            cout << "Put Yout New Age : ";
            cin >> a;
            doc.personal_info.age = a;
            cout << "Your Age was edited successfullly.\n";
        }
        else if (cho == 3)
        {
            int n;
            cout << "Put your years of Experience : ";
            cin >> n;
            doc.years_of_Ex = n;
            cout << "Your Experience was edited successfully.\n";
        }
        else if (cho == 4)
        {
            string las_maj = doc.doc_major;
            cout << "Available Majors : " << nl;
            for (int i = 0; i < sz(Majors); i++)
            {
                cout << i + 1 << " | " << Majors[i] << nl;
            }
            cout << sz(Majors) + 1 << " | " << "Another major" << nl;
            cout << "-------------------\n";
            int maj;
            cout << "What is your Major ? ";
            cin >> maj;
            if (maj == sz(Majors) + 1)
            {
                string new_maj;
                cout << "Put Your Major : ";
                cin >> new_maj;
                Majors.push_back(new_maj);
                av_maj[new_maj].push_back(doc);
                doc.doc_major = new_maj;
            }
            else
            {
                doc.doc_major = Majors[maj - 1];
                av_maj[doc.doc_major].push_back(doc);
            }

            bool er = 0;
            for (auto itMaj = av_maj.begin(); itMaj != av_maj.end();)
            {
                if (itMaj->first == las_maj)
                {
                    auto &v = itMaj->second;
                    for (auto it = v.begin(); it != v.end();)
                    {
                        if (doc.personal_info.Id == it->personal_info.Id)
                            it = v.erase(it);
                        else
                            ++it;
                    }

                    if (v.empty())
                    {
                        itMaj = av_maj.erase(itMaj);
                        er = 1;
                        continue;
                    }
                }
                ++itMaj;
            }

            if (er)
            {
                for (int i = 0; i < Majors.size(); i++)
                {
                    string s = Majors[i];
                    if (s == las_maj)
                    {
                        Majors.erase(Majors.begin() + i);
                        break;
                    }
                }
            }

            cout << "Your Major was edited successfully.\n";
        }
    }

    cout << "-----------------------------\n";
    cout << "     Doctor's Information    \n";
    cout << "-----------------------------\n";
    cout << "Doctor's ID : " << doc.personal_info.Id << nl;
    cout << "Doctor's Name : " << doc.personal_info.name << nl;
    cout << "Doctor's Age : " << doc.personal_info.age << nl;
    cout << "Doctor's Gender : " << (doc.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years of Ex : " << doc.years_of_Ex << nl;
    cout << "Doctor's Major : " << doc.doc_major << nl;
    cout << "Doctor's Sallary : " << doc.Sallary << nl;
    cout << "-----------------------------\n";
}

void Show_all_doctors()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                      Show All Doctors                      \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    if (Doctor_list.empty())
    {
        cout << "No doctors available.\n";
        return;
    }
    cout << "How would you like to sort the Doctors?" << nl;
    cout << "[1] By ID" << nl;
    cout << "[2] By Name" << nl;
    cout << "[3] By Age" << nl;
    cout << "[4] By years of Experience" << nl;
    int cho;
    cout << "Choose an option [1-4]: ";
    cin >> cho;
    if (cho == 1)
    {
        sort(all(Doctor_list), sort_By_id<Doctor>);
    }
    else if (cho == 2)
    {
        sort(all(Doctor_list), sort_By_name<Doctor>);
    }
    else if (cho == 3)
    {
        sort(all(Doctor_list), sort_By_age<Doctor>);
    }
    else
    {
        sort(all(Doctor_list), sort_By_Ex<Doctor>);
    }

    cout << left << setw(8) << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(5) << "Age"
         << " | " << setw(6) << "Gender"
         << " | " << setw(6) << "Years"
         << " | " << setw(20) << "Salary"
         << nl;

    cout << string(75, '-') << nl;

    for (auto &dr : Doctor_list)
    {
        cout << left << setw(8) << dr.personal_info.Id
             << " | " << setw(20) << dr.personal_info.name
             << " | " << setw(5) << dr.personal_info.age
             << " | " << setw(6) << (dr.personal_info.Male ? "Male" : "Female")
             << " | " << setw(6) << dr.years_of_Ex
             << " | " << setw(20) << dr.Sallary
             << nl;
    }

    cout << string(75, '-') << nl;
    cout << "Total Doctors: " << Doctor_list.size() << nl;
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
}

void show_Doctor_Schedule()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                   Show Doctor schedule                     \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int searchId;
    cout << "Enter the ID of the doctor to view their schedule: ";
    cin >> searchId;

    Doctor *foundDoctor = nullptr;
    for (auto &doc : Doctor_list)
    {
        if (doc.personal_info.Id == searchId)
        {
            foundDoctor = &doc;
            break;
        }
    }

    if (foundDoctor == nullptr)
    {
        cout << "Doctor with ID " << searchId << " not found.\n";
        return;
    }

    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
    cout << "                               Schedule for Dr. " << foundDoctor->personal_info.name << "\n";
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";

    if (foundDoctor->schedule.empty())
    {
        cout << "This doctor has no appointments scheduled.\n";
        return;
    }

    cout << left << setw(15) << "Date"
         << " | " << setw(8) << "Patient ID"
         << " | " << setw(20) << "Patient Name"
         << " | " << setw(5) << "Age" << endl;
    cout << string(60, '-') << endl;

    for (const auto &appointment : foundDoctor->schedule)
    {
        const auto &date = appointment.first;
        const auto &patient = appointment.second;

        cout << left << setw(15) << (date.day + "/" + date.month + "/" + YEAR)
             << " | " << setw(8) << patient.personal_info.Id
             << " | " << setw(20) << patient.personal_info.name
             << " | " << setw(5) << patient.personal_info.age
             << endl;
    }

    cout << string(60, '-') << endl;
    cout << "Total Appointments: " << foundDoctor->schedule.size() << endl;
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
}

// Nurse Management System
// Add new Nurse
// Edit Exist Nurse
// Show all Nurses
// Show Nurse's List
void Add_Nurse()
{
    Nurse nr;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                         Add New Nurse                      \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int x;
    cout << "What is the National ID: ";
    cin >> x;
    bool found = 1;
    while (found)
    {
        found = 0;
        for (int i = 0; i < sz(Nurse_list); i++)
        {
            if (x == Nurse_list[i].personal_info.Id)
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            cout << "This is Invalid ID!\n";
            cout << "Please put Valid ID : ";
            cin >> x;
        }
    }
    cout << "Valid ID!" << nl;
    cout << "Enter Nurse Name: ";
    cin.ignore();
    getline(cin, nr.personal_info.name);

    cout << "Enter Nurse Age: ";
    cin >> nr.personal_info.age;

    cout << "Male / Female" << nl;
    cout << "[1] Male" << nl;
    cout << "[2] Female" << nl;
    int gn;
    cout << "Enter Nurse gender: ";
    cin >> gn;
    if (gn == 2)
        nr.personal_info.Male = 0;

    cout << "How Many years of Experience? ";
    cin >> nr.years_of_Ex;
    // generate sllary
    int Ex = nr.years_of_Ex;
    if (Ex < 2)
        nr.Sallary = 4000.0;
    else if (Ex >= 2 && Ex < 8)
        nr.Sallary = 9000.5;
    else if (Ex >= 8 && Ex < 12)
        nr.Sallary = 14000.89;
    else
        nr.Sallary = 20000.677;

    if (!Patient_list.empty())
    {
        int indx = nr.personal_info.Id % Patient_list.size();
        nr.cur_pa.push_back(Patient_list[indx]);
    }
    Nurse_list.push_back(nr);
    cout << "Nurse Added succesfuly!" << nl;

    cout << "-----------------------------\n";
    cout << "      Nurse Information      \n";
    cout << "-----------------------------\n";
    cout << "ID: " << nr.personal_info.Id << nl;
    cout << "Name: " << nr.personal_info.name << nl;
    cout << "Age: " << nr.personal_info.age << nl;
    cout << "Gender: " << (nr.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years_of_Experience: " << nr.years_of_Ex << nl;
    cout << "Sallary: " << (double)nr.Sallary << " $" << nl;
    cout << "Current Patients Count: " << nr.cur_pa.size() << nl;
    cout << "-----------------------------\n";
}

void Edit_Nurse()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                        Edit Nurse                          \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int x;
    cout << "Search about Nurse with Id : ";
    cin >> x;

    bool found = 0;
    int indx = -1;
    while (!found)
    {
        for (int i = 0; i < sz(Nurse_list); i++)
        {
            int y = Nurse_list[i].personal_info.Id;
            if (x == y)
            {
                found = 1, indx = i;
                break;
            }
        }

        if (!found)
        {
            cout << "This ID Not Exist!" << nl;
            cout << "please put correct ID : ";
            cin >> x;
        }
    }

    Nurse nur = Nurse_list[indx];
    cout << "-------------------------------\n";
    cout << "      Current information      \n";
    cout << "-------------------------------\n";
    cout << "Nurse's ID : " << nur.personal_info.Id << nl;
    cout << "Nurse's Name : " << nur.personal_info.name << nl;
    cout << "Nurse's Age : " << nur.personal_info.age << nl;
    cout << "Nurse's Gender : " << (nur.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years of Ex : " << nur.years_of_Ex << nl;
    cout << "Nurse's Sallary : " << nur.Sallary << nl;
    cout << "Current Patients Count : " << nur.cur_pa.size() << nl;
    cout << "-------------------------------\n";

    int cho = 0;

    while (cho != 4)
    {
        cout << "Choose what do you want to change\n";
        cout << "[1] Name\n";
        cout << "[2] Age\n";
        cout << "[3] Years of Experience\n";
        cout << "[4] Finish\n";
        cout << "Put your Choice : ";
        cin >> cho;

        if (cho == 1)
        {
            string s;
            cin.ignore();
            cout << "Put your New Name : ";
            getline(cin, s);
            nur.personal_info.name = s;
            cout << "Your name was edited successfully.\n";
        }
        else if (cho == 2)
        {
            int a;
            cout << "Put Your New Age : ";
            cin >> a;
            nur.personal_info.age = a;
            cout << "Your Age was edited successfully.\n";
        }
        else if (cho == 3)
        {
            int n;
            cout << "Put your years of Experience : ";
            cin >> n;
            nur.years_of_Ex = n;
            cout << "Your Experience was edited successfully.\n";
            nur.Sallary = (double)Sallary_generator(nur.years_of_Ex);
        }
    }

    Nurse_list[indx] = nur;

    cout << "-----------------------------\n";
    cout << "     Nurse's Information     \n";
    cout << "-----------------------------\n";
    cout << "Nurse's ID : " << nur.personal_info.Id << nl;
    cout << "Nurse's Name : " << nur.personal_info.name << nl;
    cout << "Nurse's Age : " << nur.personal_info.age << nl;
    cout << "Nurse's Gender : " << (nur.personal_info.Male ? "Male" : "Female") << nl;
    cout << "Years of Ex : " << nur.years_of_Ex << nl;
    cout << "Nurse's Sallary : " << nur.Sallary << nl;
    cout << "Current Patients Count : " << nur.cur_pa.size() << nl;
    cout << "-----------------------------\n";
}

void Show_all_nurses()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                      Show All Nurses                       \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    if (Nurse_list.empty())
    {
        cout << "No nurses available.\n";
        return;
    }

    cout << "How would you like to sort the Nurses?" << nl;
    cout << "[1] By ID" << nl;
    cout << "[2] By Name" << nl;
    cout << "[3] By Age" << nl;
    cout << "[4] By years of Experience" << nl;
    int cho;
    cout << "Choose an option [1-4]: ";
    cin >> cho;

    if (cho == 1)
    {
        sort(all(Nurse_list), sort_By_id<Nurse>);
    }
    else if (cho == 2)
    {
        sort(all(Nurse_list), sort_By_name<Nurse>);
    }
    else if (cho == 3)
    {
        sort(all(Nurse_list), sort_By_age<Nurse>);
    }
    else
    {
        sort(all(Nurse_list), sort_By_Ex<Nurse>);
    }

    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
    cout << "                                       Schedule  \n";
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";

    cout << left << setw(8) << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(5) << "Age"
         << " | " << setw(6) << "Gender"
         << " | " << setw(6) << "Years"
         << " | " << setw(12) << "Salary"
         << " | " << setw(8) << "Patients"
         << nl;

    cout << string(90, '-') << nl;

    for (auto &nr : Nurse_list)
    {
        cout << left << setw(8) << nr.personal_info.Id
             << " | " << setw(20) << nr.personal_info.name
             << " | " << setw(5) << nr.personal_info.age
             << " | " << setw(6) << (nr.personal_info.Male ? "Male" : "Female")
             << " | " << setw(6) << nr.years_of_Ex
             << " | " << setw(12) << nr.Sallary
             << " | " << setw(8) << nr.cur_pa.size()
             << nl;
    }

    cout << string(90, '-') << nl;
    cout << "Total Nurses: " << Nurse_list.size() << nl;
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-\n";
}
void show_Nurse_Patients()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                  Show Nurse Patients                       \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    int searchId;
    cout << "Enter the ID of the nurse to view their patients: ";
    cin >> searchId;

    Nurse *foundNurse = nullptr;
    for (auto &nr : Nurse_list)
    {
        if (nr.personal_info.Id == searchId)
        {
            foundNurse = &nr;
            break;
        }
    }

    if (foundNurse == nullptr)
    {
        cout << "Nurse with ID " << searchId << " not found.\n";
        return;
    }

    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
    cout << "               Patients under Nurse " << foundNurse->personal_info.name << "\n";
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

    if (foundNurse->cur_pa.empty())
    {
        cout << "This nurse currently has no patients assigned.\n";
        return;
    }

    cout << left << setw(8) << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(5) << "Age"
         << " | " << setw(8) << "Gender"
         << nl;

    cout << string(50, '-') << nl;

    for (const auto &patient : foundNurse->cur_pa)
    {
        cout << left << setw(8) << patient.personal_info.Id
             << " | " << setw(20) << patient.personal_info.name
             << " | " << setw(5) << patient.personal_info.age
             << " | " << setw(8) << (patient.personal_info.Male ? "Male" : "Female")
             << nl;
    }

    cout << string(50, '-') << nl;
    cout << "Total Patients: " << foundNurse->cur_pa.size() << nl;
    cout << "-=-=-=-==--=-=-=--=--=-=-=-=-=--=-=-=-=--=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
}

void Add_medicine()
{
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                    Add New Medicine                        \n";
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    Medicine m;
    cout << "Enter Medicine ID: ";
    cin >> m.Id;
    cin.ignore();

    cout << "Enter Medicine Name: ";
    getline(cin, m.Name);

    cout << "Enter Quantity: ";
    cin >> m.quantity;

    cout << "Enter Price: ";
    cin >> m.price;

    Parmacy.push_back(m);

    cout << "Medicine added successfully!\n";
}

void View_All_Medicines()
{
    if (Parmacy.empty())
    {
        cout << "No medicines available.\n";
        return;
    }

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                   All Medicines in Pharmacy                 \n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    cout << left << setw(8) << "ID"
         << " | " << setw(20) << "Name"
         << " | " << setw(10) << "Quantity"
         << " | " << setw(10) << "Price"
         << nl;

    cout << string(60, '-') << nl;

    for (const auto &m : Parmacy)
    {
        cout << left << setw(8) << m.Id
             << " | " << setw(20) << m.Name
             << " | " << setw(10) << m.quantity
             << " | " << setw(10) << fixed << setprecision(2) << m.price
             << nl;
    }

    cout << string(60, '-') << nl;
    cout << "Total Medicines: " << Parmacy.size() << nl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

void Search_Medicine()
{
    if (Parmacy.empty())
    {
        cout << "No medicines available to search.\n";
        return;
    }
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "                   All Medicines in Pharmacy                 \n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    int choice;
    cout << "\nSearch By: \n";
    cout << "1) ID\n";
    cout << "2) Name\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    bool found = false;
    if (choice == 1)
    {
        int id;
        cout << "Enter Medicine ID: ";
        cin >> id;

        for (const auto &m : Parmacy)
        {
            if (m.Id == id)
            {
                cout << "Medicine Found:\n";
                cout << "ID: " << m.Id << "Name: " << m.Name << nl
                     << "Quantity: " << m.quantity << nl
                     << "Price: " << m.price << "\n";
                found = true;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        string name;
        cout << "Enter Medicine Name: ";
        getline(cin, name);

        for (const auto &m : Parmacy)
        {
            if (m.Name == name)
            {
                cout << "Medicine Found:\n";
                cout << "ID: " << m.Id << "\nName: " << m.Name << nl
                     << "Quantity: " << m.quantity << nl
                     << "Price: " << m.price << "\n";
                found = true;
                break;
            }
        }
    }

    if (!found)
        cout << "Medicine not found.\n";
}
void Delete_Medicine()
{
    if (Parmacy.empty())
    {
        cout << "No medicines available to delete.\n";
        return;
    }

    int id;
    cout << "Enter Medicine ID to delete: ";
    cin >> id;

    for (auto it = Parmacy.begin(); it != Parmacy.end(); ++it)
    {
        if (it->Id == id)
        {
            cout << "Medicine \"" << it->Name << "\" deleted successfully!\n";
            Parmacy.erase(it);
            return;
        }
    }
    cout << "Medicine with ID " << id << " not found.\n";
}

void Menu();
void side_menu(int op)
{
    if (op == 1)
    {
        int cho;
        while (cho != 4)
        {
            cout << "------------------------------------------------------------\n";
            cout << "           Patient Management System - Side Menu           \n";
            cout << "------------------------------------------------------------\n";
            cout << " 1) Add Patient\n";
            cout << " 2) Edit Patient\n";
            cout << " 3) Show all patients\n";
            cout << " 4) Main Menu\n";
            cout << "------------------------------------------------------------\n";
            cout << "Enter Your choice : ";
            cin >> cho;
            cout << nl;

            if (cho == 1)
            {
                Add_New_Patient();
            }
            else if (cho == 2)
            {
                Edit_Patient();
            }
            else if (cho == 3)
            {
                Print_all_patients();
            }
        }
    }
    else if (op == 2)
    {
        int cho;
        while (cho != 5)
        {
            cout << "------------------------------------------------------------\n";
            cout << "           Doctor Management System - Side Menu           \n";
            cout << "------------------------------------------------------------\n";
            cout << " 1) Add Doctor\n";
            cout << " 2) Edit Doctor\n";
            cout << " 3) show all Doctors\n";
            cout << " 4) Show Doctor schedule\n";
            cout << " 5) Main Menu\n";
            cout << "------------------------------------------------------------\n";
            cout << "Enter Your choice : ";
            cin >> cho;
            cout << nl;
            if (cho == 1)
            {
                Add_Doctor();
            }
            else if (cho == 2)
            {
                Edit_Doctor();
            }
            else if (cho == 3)
            {
                Show_all_doctors();
            }
            else if (cho == 4)
            {
                show_Doctor_Schedule();
            }
        }
    }
    else if (op == 3)
    {
        int cho;
        while (cho != 5)
        {
            cout << "------------------------------------------------------------\n";
            cout << "           Nurse Management System - Side Menu           \n";
            cout << "------------------------------------------------------------\n";
            cout << " 1) Add Nurse\n";
            cout << " 2) Edit Nurse\n";
            cout << " 3) Show all Nurses\n";
            cout << " 4) Show Nurse Patients\n";
            cout << " 5) Main Menu\n";
            cout << "------------------------------------------------------------\n";
            cout << "Enter Your choice : ";
            cin >> cho;
            cout << nl;
            if (cho == 1)
            {
                Add_Nurse();
            }
            else if (cho == 2)
            {
                Edit_Nurse();
            }
            else if (cho == 3)
            {
                Show_all_nurses();
            }
            else if (cho == 4)
            {
                show_Nurse_Patients();
            }
        }
    }
    else if (op == 4)
    {
        int cho;
        while (cho != 5)
        {
            cout << "------------------------------------------------------------\n";
            cout << "                    Pharmacy Section                        \n";
            cout << "------------------------------------------------------------\n";
            cout << " 1) Add Medicine\n";
            cout << " 2) View All Medicines\n";
            cout << " 3) Search about specific Medicine\n";
            cout << " 4) Delete Medicine\n";
            cout << " 5) Main Menu\n";
            cout << "------------------------------------------------------------\n";
            cout << "Enter your choice: ";
            cin >> cho;
            if (cho == 1)
            {
                Add_medicine();
            }
            else if (cho == 2)
            {
                View_All_Medicines();
            }
            else if (cho == 3)
            {
                Search_Medicine();
            }
            else if (cho == 4)
            {
                Delete_Medicine();
            }
        }
    }
}

void Menu()
{
    while (true)
    {
        cout << "============================================================\n";
        cout << "           Hospital Management System - Main Menu           \n";
        cout << "============================================================\n";
        cout << "[1] Patient Management\n";
        cout << "[2] Doctor Management\n";
        cout << "[3] Nursing Management\n";
        cout << "[4] Parmacy\n";
        cout << "[0] Exit\n";
        cout << "============================================================\n";
        int op;
        cout << "Enter Your Choice : ";
        cin >> op;
        cout << nl;

        if (op > 5)
        {
            cout << "Invalid choice. Please try again.\n";
        }
        else if (op == 0)
        {
            cout << "============================================================\n";
            cout << "                  HOSPITAL MANAGEMENT SYSTEM                \n";
            cout << "============================================================\n";
            cout << "                    Program Terminated                      \n";
            cout << "                 Thank you and Have a nice day!             \n";
            cout << "============================================================\n";
            break;
        }
        else
        {
            side_menu(op);
        }
    }
}

int main()
{
    fill_Majors();
    fill_Doctors();
    fill_Nurses();
    fill_Pharmacy();
    Menu();
    return 0;
}
