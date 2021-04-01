#include "readFromFile.h"

vector<string> file_to_vector(const string& filename) {
    ifstream text(filename);
    string line;
    vector<string> out;
    if (text.is_open()) {
        istream_iterator<string> iter(text);
        while (!text.eof()) {
            out.push_back(*iter);
            ++iter;
        }
    }
    return out;
}

vector<string*> extract_required_info(const vector<string> vec) {
    // source, stops, destination
    vector<string*> all_data;
    for (auto line : vec) {
        stringstream ss(line);
        vector<string> vec_line;
        while (ss.good()) {
            string substring;
            getline(ss, substring, ',');
            vec_line.push_back(substring);
            
            if (vec_line.size() == 8) {
                string* info = new string(vec_line[2] + "," +  vec_line[7] + "," + vec_line[4]);
                all_data.push_back(info);
            } else {
                continue;
            }
        }
    }
    return all_data;
}


