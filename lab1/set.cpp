#include "Header.h"

MyString::MyString() {
    str = nullptr;  
    length = 0;     
}
MyString::MyString(const char* str) {
    if (str == nullptr) {
        this->str = nullptr;
        length = 0;
    }
    else {
        length = strlen(str);
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++) {
            this->str[i] = str[i];
        }
        this->str[length] = '\0';
    }
}
MyString::~MyString() {
    delete[] this->str;
}

MyString::MyString(const MyString& other) {
    length = strlen(other.str);
    this->str = new char[length + 1];
    for (int i = 0; i < length; i++) {
        this->str[i] = other.str[i];
    }
    this->str[length] = '\0';
}

MyString::MyString(MyString&& other) {
    this->length = other.length;
    this->str = other.str;
    other.str = nullptr;
}

MyString& MyString::operator =(const MyString& other) {
    if (this == &other) return *this; 

    delete[] str; 

    length = other.length; 
    if (length > 0) {
        str = new char[length + 1];  
        strcpy_s(str, length + 1, other.str);
    }
    else {
        str = nullptr;  
    }

    return *this;
}

bool MyString::operator ==(const MyString& other) const {
    if (this->length != other.length) {
        return false;
    }
    for (int i = 0; i < this->length; i++) {
        if (this->str[i] != other.str[i]) {
            return false;
        }
    }
    return true;
}

bool MyString::operator !=(const MyString& other) const {
    return !(*this == other);
}

void MyString::Add(const char* el) {
    if (isInSet(el)) {
        return;
    }
    int elLength = strlen(el);
    int newLength = length + elLength + (length > 0 ? 1 : 0);
    char* newStr = new char[newLength + 1];

    if (length > 0) {
        for (int i = 0; i < length; i++) {
            newStr[i] = this->str[i];
        }
        newStr[length] = ',';
    }

    for (int i = 0; i < elLength; i++) {
        newStr[length + (length > 0 ? 1 : 0) + i] = el[i];
    }
    newStr[newLength] = '\0';
    delete[] this->str;
    this->str = newStr;
    length = newLength;
}

MyString MyString::operator +(const MyString& other) const {
    MyString result = *this;
    int otherLength = strlen(other.str);
    for (int i = 0; i < otherLength; i++) {
        char currentElement[20];
        int j = 0;
        while (i < otherLength && other.str[i] != ',') {
            currentElement[j++] = other.str[i++];
        }
        currentElement[j] = '\0';
        result.Add(currentElement);
    }
    return result;
}

MyString MyString::operator *(const MyString& other) const {
    MyString result;
    int otherLength = strlen(other.str);
    for (int i = 0; i < otherLength; i++) {
        char currentElement[20];
        int j = 0;
        while (i < otherLength && other.str[i] != ',') {
            currentElement[j++] = other.str[i++];
        }
        currentElement[j] = '\0';
        if (isInSet(currentElement)) {
            result.Add(currentElement);
        }
    }
    return result;
}

MyString MyString::operator -(const MyString& other) const {
    MyString result = *this;
    int otherLength = strlen(other.str);
    for (int i = 0; i < otherLength; i++) {
        char currentElement[20];
        int j = 0;
        while (i < otherLength && other.str[i] != ',') {
            currentElement[j++] = other.str[i++];
        }
        currentElement[j] = '\0';
        result.Remove(currentElement);
    }
    return result;
}

void MyString::Remove(const char* el) {
    int elLength = strlen(el);
    char* newStr = new char[length + 1];
    int newLength = 0;
    for (int i = 0; i < length; i++) {
        char currentElement[20];
        int j = 0;
        while (i < length && str[i] != ',') {
            currentElement[j++] = str[i++];
        }
        currentElement[j] = '\0';
        if (strcmp(currentElement, el) != 0) {
            if (newLength > 0) {
                newStr[newLength++] = ',';
            }
            for (int k = 0; currentElement[k] != '\0'; k++, newLength++) {
                newStr[newLength] = currentElement[k];
            }
        }
    }
    newStr[newLength] = '\0';
    delete[] str;
    str = newStr;
    length = newLength;
}

bool MyString::isInSet(const char* el) const {
    for (int i = 0; i < length; i++) {
        char currentElement[20];
        int j = 0;
        while (i < length && str[i] != ',') {
            currentElement[j++] = str[i++];
        }
        currentElement[j] = '\0';
        if (strcmp(currentElement, el) == 0) {
            return true;
        }
    }
    return false;
}

int MyString::Cardinality() const {
    if (length == 0) return 0;
    int count = 0;
    bool inElement = false;
    int bracketCount = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] == '{') {
            bracketCount++;
            if (!inElement) {
                inElement = true;
            }
        }
        else if (str[i] == '}') {
            bracketCount--;
        }
        else if (str[i] != ',') {
            if (!inElement && bracketCount == 0) {
                count++;
                inElement = true;
            }
        }
        else {
            if (inElement && bracketCount == 0) {
                inElement = false;
            }
        }
    }

    if (inElement) {
        count++;
    }

    return count;
}

void MyString::PrintPowerSet() const {
    int r = 1 << Cardinality(); 
    for (int i = 0; i < r; i++) {
        PrintSubset(i); 
    }
}

void MyString::PrintSubset(int n) const {
    int index = 0;
    std::cout << "{";

    bool first = true; 
    while (n) {
        if (n & 1) {
            if (!first) {
                std::cout << " , "; 
            }
            std::cout << GetElement(index); 
            first = false; 
        }
        index++;
        n >>= 1;
    }
    std::cout << "}\n"; 
}

const char* MyString::GetElement(int index) const {
    int currentIndex = 0;
    char* currentElement = new char[20];
    int j = 0;

    for (int i = 0; i < length; i++) {
        if (str[i] != ',') {
            currentElement[j++] = str[i];
        }
        else {
            currentElement[j] = '\0';
            if (currentIndex == index) {
                return currentElement;
            }
            currentIndex++;
            j = 0;
        }
    }

    currentElement[j] = '\0';
    if (currentIndex == index) {
        return currentElement;
    }

    delete[] currentElement;
    return nullptr;
}

void MyString::Print() const {
    if (str) {
        std::cout << str << std::endl;
    }
    else {
        std::cout << "Пустое множество" << std::endl;
    }
}

bool MyString::IsEmpty() {
    if (str == nullptr || length == 0) {
        return true;
    }
    else {
        return false;
    }
}