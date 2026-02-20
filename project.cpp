#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <limits>
#include <random>
#include <cctype>
#include <cmath>

void showMenu()
{
    std::cout << "1. Admin\n2. patient\n3. visitor\n";
    std::cout << "select user type:";
}

struct user
{
    std::string name;
    std::string password;
    std::string role;
};

std::string role_choicing(int choice)
{
    switch (choice)
    {
    case 1:
        return "admin";
    case 2:
        return "patient";
    case 3:
        return "visitor";
    default:
        return "";
    }
}

bool signUp(const user &u)
{
    std::ofstream file("usersInf.txt", std::ios::app);
    if (!file)
    {
        std::cout << "Error opening users file for writing!\n";
        exit(1);
    }
    int upper = 0, digit = 0, lower = 0;
    for (unsigned char i : u.password)
    {
        if (std::islower(i))
            lower++;
        if (std::isupper(i))
            upper++;
        if (std::isdigit(i))
            digit++;
    }

    if (u.password.length() < 8 || upper < 1 || lower < 1 || digit < 1)
    {
        std::cout << "\n you'r password is not a strong password,\n"
                  << "your password must have at least 1 digit , 1 alpha and upper and lower alpha!\n\n";
        exit(1);
    }
    else
    {
        file << u.name << '\t'
             << u.password << '\t'
             << u.role << '\n';
        std::cout << "Signup successful!\n";
        return true;
    }
}

bool signIn(const user &u)
{
    std::ifstream infile("usersInf.txt");

    if (!infile)
    {
        std::cerr << "we can't open the file! " << std::endl;
        return false;
    }
    std::string line;

    std::string record = u.name + '\t' + u.password + '\t' + u.role;

    while (std::getline(infile, line))
    {
        if (line == record)
        {
            return true;
        }
    }

    return false;
}

void takeInformations(user &u)
{
    std::cout << "please inter your name: ";
    getline(std::cin, u.name);

    std::cout << "please inter your password: ";
    getline(std::cin, u.password);
}

struct patient
{
    std::string Gender;
    std::string age;
    std::string Weight;
    std::string Height;
    std::string nationalNumber;
    int symptoms;
    std::string DrugsPrescription;
};

struct symptoms
{
    bool Heavy_bleeding = false;       // 1 - خونریزی شدید
    bool Heart_palpitation = false;    // 2 - تپش قلب
    bool Concussio = false;            // 3 - ضربه مغزی
    bool Amputation = false;           // 4 - قطع عضو
    bool injuries_accident = false;    // 5 - آسیب ناشی از تصادف
    bool Burn_injury = false;          // 6 - سوختگی
    bool difficulty_breathing = false; // 7 - خفگی و تنگی نفس
    bool Heart_attack = false;         // 8 - حمله قلبی
    bool stress = false;               // 9 - استرس
};

void checking_symptoms(symptoms &current_patient, int num)
{
    switch (num)
    {
    case 1:
        current_patient.Heavy_bleeding = true;
        break;
    case 2:
        current_patient.Heart_palpitation = true;
        break;
    case 3:
        current_patient.Concussio = true;
        break;
    case 4:
        current_patient.Amputation = true;
        break;
    case 5:
        current_patient.injuries_accident = true;
        break;
    case 6:
        current_patient.Burn_injury = true;
        break;
    case 7:
        current_patient.difficulty_breathing = true;
        break;
    case 8:
        current_patient.Heart_attack = true;
        break;
    case 9:
        current_patient.stress = true;
        break;
    }
}

void patientFile(patient &u, symptoms &s)
{
    std::cout << "please inter your gender: ";
    getline(std::cin, u.Gender);

    std::cout << "please inter your Age: ";
    getline(std::cin, u.age);

    std::cout << "please inter your Weight: ";
    getline(std::cin, u.Weight);

    std::cout << "please inter your height: ";
    getline(std::cin, u.Height);

    std::cout << "please inter your National number: ";
    getline(std::cin, u.nationalNumber);

    std::cout << "\n\nplease inter your symptoms Number:\n1-Heavy bleeding\n2-Heart palpitations\n"
              << "3-Concussion\n4-Amputation\n5-Severe injuries from an accident\n6-Burn injury\n"
              << "7- Difficulty breathing\n8-Heart attack\n9- stress\ninter 'e' to end\n";

    symptoms user_current_symptoms;

    while (std::cin >> u.symptoms)
    {
        int current_symptom = u.symptoms;
        checking_symptoms(user_current_symptoms, current_symptom);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "please inter your prescription Drugs: ";
    getline(std::cin, u.DrugsPrescription);

    std::ofstream patientFile("patientFile.txt", std::ios::app);

    patientFile << "Gender: " << u.Gender << "\n"
                << "age: " << u.age << '\n'
                << "weight: " << u.Weight << '\n'
                << "National Number: " << u.nationalNumber << '\n'
                << "drugs: " << u.DrugsPrescription << '\n';

    if (user_current_symptoms.Amputation == true)
    {
        patientFile << "symptom: " << "Ampution\n";
        s.Amputation = true;
    }
    if (user_current_symptoms.Burn_injury == true)
    {
        patientFile << "symptom: " << "Burn injury\n";
        s.Burn_injury = true;
    }
    if (user_current_symptoms.Concussio == true)
    {
        patientFile << "symptom: " << "concussion\n";
        s.Concussio = true;
    }
    if (user_current_symptoms.difficulty_breathing == true)
    {
        patientFile << "symptom: " << "difficulty of breathing\n";
        s.difficulty_breathing = true;
    }
    if (user_current_symptoms.Heart_attack == true)
    {
        patientFile << "symptom: " << "Heart attack\n";
        s.Heart_attack = true;
    }
    if (user_current_symptoms.Heart_palpitation == true)
    {
        patientFile << "symptom: " << "heart palpitation\n";
        s.Heart_palpitation = true;
    }
    if (user_current_symptoms.Heavy_bleeding)
    {
        patientFile << "symptom: " << "heavy bleeding\n";
        s.Heavy_bleeding = true;
    }
    if (user_current_symptoms.injuries_accident)
    {
        patientFile << "symptom: " << "accident injury\n";
        s.injuries_accident = true;
    }
    if (user_current_symptoms.stress == true)
    {
        patientFile << "symptom: " << "stress\n";
        s.stress = true;
    }
}

struct hospital_departments
{
    bool emergencyDepartment = false;  // بخش اورژانس
    bool PsychiatryDepartment = false; // بخش روان
    bool PediatricsDepartment = false; // بخش اطفال
};

int urgentOrNot(symptoms &s)
{
    return (s.Amputation || s.Burn_injury || s.Concussio || s.difficulty_breathing || s.Heart_attack || s.Heart_palpitation || s.Heavy_bleeding || s.injuries_accident);
}

void teriage_patient(patient &p, symptoms &s, hospital_departments &h)
{
    if (urgentOrNot(s))
    {
        h.emergencyDepartment = true;
        std::cout << "\nplease go to emergency department :) " << std::endl;
    }
    else if (s.stress == true)
    {
        h.PsychiatryDepartment = true;
        std::cout << "\nplease go to Psychiatry Department :)" << std::endl;
    }
    else if (std::stoi(p.age) < 18)
    {
        h.PediatricsDepartment = true;
        std::cout << "\n\nplease go to pediatric department :)" << std::endl;
    }
}

void bloodPresureTaking(int &naclUse, int &SBP, patient p)
{
    std::cout << "\nplease Enter how much you use nacl daily?\n1-Rarely(0 - 2 mg)\n2-sometimes(2 - 5mg)\n3- somuch(5 mg) :\n";
    std::cin >> naclUse;
    int weight = std::stoi(p.Weight);
    int option = 0;
    switch (naclUse)
    {
    case 1:
        option += 1;
        break;
    case 2:
        option += 2;
        break;
    case 3:
        option += 3;
        break;
    default:
        std::cout << "plz inter a valid value! ";
        return;
    }
    SBP = weight + 40 + option;
    std::cout << "you'r SBP is: " << SBP << std::endl;
    std::ofstream patientFile("patientFile.txt", std::ios::app);
    patientFile << "patient SBP is: " << SBP << std::endl;
    patientFile.close();
}

int drugInteraction()
{
    int patientAnswer;
    std::cout << "Do you use any pain killer?\n1-Yes\n2-No" << std::endl;
    std::cin >> patientAnswer;
    if (patientAnswer == 1)
    {
        std::ifstream file("patientFile.txt");
        std::string word, target = "warfarin";
        while (file >> word)
        {
            if (word == target)
            {
                return true;
            }
        }
    }
    return false;
}

void blood_group(std::string &patient_bloodGroup, int &patient_RH)
{
    int userChoice;
    std::string father_blood;
    std::cout << "plz choose your father blood group:\n1- A\n2- B\n3- AB\n4- O\n";
    std::cin >> userChoice;

    switch (userChoice)
    {
    case 1:
        father_blood = "A";
        break;
    case 2:
        father_blood = "B";
        break;
    case 3:
        father_blood = "AB";
        break;
    case 4:
        father_blood = "O";
        break;
    }

    std::cout << "plz choose your Mother blood group:\n1- A\n2- B\n3- AB\n4- O\n";
    std::cin >> userChoice;
    std::string mother_blood;
    switch (userChoice)
    {
    case 1:
        mother_blood = "A";
        break;
    case 2:
        mother_blood = "B";
        break;
    case 3:
        mother_blood = "AB";
        break;
    case 4:
        mother_blood = "O";
        break;
    }

    int motherRH; // 0 : NEGATIVE 1: POSITIVE
    std::cout << "choose your mother Rh:\n0 : negative\n1 : positive" << std::endl;
    std::cin >> motherRH;

    int fatherRH;
    std::cout << "choose your father RH:\n0 : negative\n1 : positive" << std::endl;
    std::cin >> fatherRH;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 3);

    int randomNumer = dist(rng);
    bool father_blood_is_o = father_blood == "O";
    bool mother_blood_is_o = mother_blood == "O";
    int my_random = randomNumer % 2;

    if (father_blood == "AB" || mother_blood == "AB")
    {
        switch (randomNumer)
        {
        case 1:
            patient_bloodGroup = "A";
            break;
        case 2:
            patient_bloodGroup = "B";
            break;
        case 3:
            patient_bloodGroup = "AB";
            break;
        }
    }
    else if (father_blood == "O" && mother_blood == "O")
    {
        patient_bloodGroup = "O";
    }
    else if (father_blood_is_o != mother_blood_is_o)
    {
        if (mother_blood != "O")
            patient_bloodGroup = mother_blood;
        else if (father_blood != "O")
            patient_bloodGroup = father_blood;
    }
    else if ((father_blood == "A" && mother_blood != "A") || (mother_blood == "A" && father_blood != "A"))
    {
        patient_bloodGroup = (my_random == 0) ? "A" : "B";
    }
    else if ((father_blood == "B" && mother_blood != "B") || (mother_blood == "B" && father_blood != "B"))
    {
        patient_bloodGroup = (my_random == 0) ? "A" : "B";
    }
    else if ((father_blood == "B") && (mother_blood == "B"))
    {
        patient_bloodGroup = "B";
    }
    else if ((mother_blood == "A") && (father_blood == "A"))
    {
        patient_bloodGroup = "A";
    }

    // RH calculation
    if ((motherRH == 0) && (fatherRH == 0))
    {
        patient_RH = 0;
    }
    else if ((motherRH == 0 && fatherRH != 0) || (fatherRH == 0 && motherRH != 0))
    {
        patient_RH = (my_random == 0) ? 0 : 1;
    }
    else
    {
        patient_RH = 1;
    }

    std::ofstream patientFile("patientFile.txt", std::ios::app);
    if (patient_bloodGroup == "A" && patient_RH == 1)
        patient_bloodGroup = "A+";
    else if (patient_bloodGroup == "A" && patient_RH == 0)
        patient_bloodGroup = "A-";
    else if (patient_bloodGroup == "B" && patient_RH == 1)
        patient_bloodGroup = "B+";
    else if (patient_bloodGroup == "B" && patient_RH == 0)
        patient_bloodGroup = "B-";
    else if (patient_bloodGroup == "O" && patient_RH == 1)
        patient_bloodGroup = "O+";
    else if (patient_bloodGroup == "O" && patient_RH == 0)
        patient_bloodGroup = "O-";

    patientFile << "patient blood group is: " << patient_bloodGroup << "\n";
}

int GSS_calculation(symptoms &s, user c)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distE(1, 4);
    std::uniform_int_distribution<int> distV(1, 5);
    std::uniform_int_distribution<int> distM(1, 6);

    int E = distE(rng); // eye response
    int V = distV(rng); // verbal response
    int M = distM(rng); // motor response
    int GCS = E + V + M;

    bool bastari;
    std::ofstream bastarie("bastari.txt", std::ios::app);
    std::ofstream tarkhiseh("tarkhis.txt", std::ios::app);

    if (GCS < 13 || s.Heavy_bleeding || s.Concussio || s.Amputation || s.injuries_accident || s.difficulty_breathing)
    {
        bastari = true;
        bastarie << "user " << c.name << " has been hospitalized ." << std::endl;
        bastarie << "............................................\n";
    }
    else
    {
        bastari = false;
        tarkhiseh << c.name << " Discharge from the hospital. ";
        tarkhiseh << "...........................................\n";
    }
    return GCS;
}

struct phsyco_patient_type
{
    bool Anxiety = false;
    bool Depression = false;
    bool Stress = false;
};

int QTake(int &x)
{
    while (true)
    {
        if (!(std::cin >> x))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ohhh! you Entered a not valid value,\nplease inter a valid value:\n";
            continue;
        }
        if (x >= 1 && x <= 4)
            return x;

        std::cout << "ohhh! you Entered a not valid value,\nplease inter a valid value:\n";
    }
}

void questionBox()
{
    std::ofstream patientFile("patientFile.txt", std::ios::app);
    int anxiety = 0;
    int depression = 0;
    int stress = 0;

    int bullsheee = 0;
    //.................................................................................................
    std::cout << "\n\n\n";
    std::cout << "///////////////////////////////////////////////////////////////////////";
    std::cout << "ANXITETY";
    std::cout << "///////////////////////////////////////////////////////////////////////";

    std::cout << "\nThese questions measure your level of anxiety. Please choose a number between 1 and 4."
              << "\n1:It does not apply to me at all.\n"
              << "2‌:It applies to me to a small extent.\n3:It applies to me to a large extent."
              << "\n4:It applies to me completely and intensely.\n\n";

    std::cout << "I worry too much about everyday matters.\n";
    anxiety += QTake(bullsheee);
    std::cout << "If someone is upset with me, it is very important to me.\n";
    anxiety += QTake(bullsheee);
    std::cout << "I feel anxious when talking to strangers.\n";
    anxiety += QTake(bullsheee);
    //...............................................................................................
    std::cout << "\n\n\n";
    std::cout << "///////////////////////////////////////////////////////////////////////";
    std::cout << "DEPRESSION";
    std::cout << "///////////////////////////////////////////////////////////////////////";

    std::cout << "Feelings of guilt or worthlessness.\n";
    depression += QTake(bullsheee);
    std::cout << "I am often sad or depressed.\n";
    depression += QTake(bullsheee);
    std::cout << "I feel hopeless or pessimistic about the future.\n";
    depression += QTake(bullsheee);
    std::cout << "I criticize myself excessively.\n";
    depression += QTake(bullsheee);
    //.....................................................................................................
    std::cout << "\n\n\n";
    std::cout << "///////////////////////////////////////////////////////////////////////";
    std::cout << "STRESS";
    std::cout << "///////////////////////////////////////////////////////////////////////";

    std::cout << "In difficult situations, I feel that I lose control of things.\n";
    stress += QTake(bullsheee);
    std::cout << "I cannot easily distance myself from stressful thoughts.\n";
    stress += QTake(bullsheee);

    int level_anxiety = 3 * anxiety;
    int level_depression = 4 * depression;
    int level_stress = 2 * stress;
    //........................................................................................................
    std::string anxiety_level;
    std::string depression_level;
    std::string stress_level;

    // just for anxiety ://
    if(level_anxiety >= 3 && level_anxiety <= 6)
    {
        anxiety_level = "Low";
    }
    else if(level_anxiety >= 7 && level_anxiety <= 9)
    {
        anxiety_level = "Mid";
    }
    else if(level_anxiety >= 10 && level_anxiety <= 12)
    {
        anxiety_level = "High";
    }


    if(level_depression >= 4 && level_depression <= 8)
    {
        depression_level = "Low";
    }
    else if(level_depression >= 9 && level_depression <= 12)
    {
        depression_level = "Mid";
    }
    else if(level_depression >= 13 and level_depression <= 16)
    {
        depression_level = "High";
    }

    if(level_stress >= 2 && level_stress <= 4)
    {
        stress_level = "Low";
    }
    else if(level_stress >= 5 && level_stress <= 6)
    {
        stress_level = "Mid";
    }
    else if(level_stress >= 7 && level_stress <= 8)
    {
        stress_level = "High";
    }

    patientFile << 


}

int main()
{
    while (true)
    {
        showMenu();
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "your output is invalid, please try again/ \n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string rol_choice = role_choicing(choice);
        if (rol_choice.empty())
        {
            std::cout << "invalid choice! please select 1 , 2 or 3!. \n";
            continue;
        }

        user currentUser;
        patient currentPatient;
        symptoms currentSymptoms;
        hospital_departments currentDep;
        int naclUse = 0;
        int SBP; // patient SBP
        int RH;
        std::string patient_blood_group;

        currentUser.role = rol_choice;
        takeInformations(currentUser);

        if (signIn(currentUser))
        {
            std::cout << "Welcome " << currentUser.name << " you are an " << currentUser.role << "\n";
            if (currentUser.role == "patient")
            {
                patientFile(currentPatient, currentSymptoms);
                teriage_patient(currentPatient, currentSymptoms, currentDep);
                if (currentDep.emergencyDepartment)
                {
                    bloodPresureTaking(naclUse, SBP, currentPatient);
                    int *bloodpresurePtr = &SBP;
                    if (drugInteraction())
                    {
                        std::cout << "\nyou have drug interaction! " << std::endl;
                    }
                    blood_group(patient_blood_group, RH);
                    GSS_calculation(currentSymptoms, currentUser);
                }
                else if (currentDep.PediatricsDepartment)
                {
                    int weight = std::stoi(currentPatient.Weight);
                    int height = std::stoi(currentPatient.Height);
                    if (height > 0)
                    {
                        double h = height / 100.0;
                        double BMI = weight / (h * h);
                    }
                }
                else if (currentDep.PsychiatryDepartment)
                {
                    questionBox();
                }
            }
        }
        else
        {
            std::cout << "\n\naccout NOT found  let's signup you now! " << std::endl;
            signUp(currentUser);

            if (currentUser.role == "patient")
            {
                patientFile(currentPatient, currentSymptoms);
            }
        }
    }

    return 0;
}
