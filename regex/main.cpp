#include <iostream>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>
class LttngTraceRecord {
public:
    double timestamp;
    std::string kf_name;

private:
};

int main()
{
    FILE *pFile, *pFileReport;
    char mystring[6000];
    std::vector<LttngTraceRecord> vec_ltr;

    pFile = fopen("traces.txt", "r");
    if (pFile == NULL) {
        perror("Error opening file");
        printf("Usage: ./lttng-analyzer trace.txt\n"); 
    } else {
        while (fgets(mystring, sizeof(mystring), pFile) != NULL) {
            // e.g.  [00:57:32.541424556] (+0.000000901) paslab-cyliu
            // e.g. std::regex rgx(".*FILE_(\\w+)_EVENT\\.DAT.*");
            LttngTraceRecord ltr_tmp;
            std::smatch match;
            const std::string s(mystring);

            if (s != "") {
                std::string ss = s;
                int s_begin = ss.find_first_of("[") + 7;
                int s_end = ss.find_first_of("]") - 1;
                std::string s_timestamp = ss.substr(s_begin, s_end - s_begin + 1);
                std::cout << "match[0]: " << s_timestamp << '\n';
                ltr_tmp.timestamp = std::stod(s_timestamp, NULL);
            }

            char cstr_for_regex[100];
            char cstr_hostname[100];
            gethostname(cstr_hostname, sizeof(cstr_hostname));
            sprintf(cstr_for_regex, "%s .+:", cstr_hostname);
            std::regex rgx_kf(cstr_for_regex);
            if (std::regex_search(s.begin(), s.end(), match, rgx_kf)) {
                std::string ss = match[0];
                int s_begin = ss.find(" ") + 1;
                int s_end = ss.find(":") - 1;
                std::string kf_name = ss.substr(s_begin, s_end - s_begin + 1);
                std::cout << "match[1]: " << kf_name << '\n';
                ltr_tmp.kf_name = kf_name;
            }

            vec_ltr.push_back(ltr_tmp);
        }
        fclose(pFile);
    }


    std::map<std::string,int> kf_map;
    // show content:
    for(std::vector<LttngTraceRecord>::iterator it=vec_ltr.begin(); it!=vec_ltr.end(); ++it){
        kf_map[(*it).kf_name] = 1;
    }

    int kf_id=0;
    for(std::map<std::string,int>::iterator it=kf_map.begin(); it!=kf_map.end(); ++it){
        (*it).second = kf_id++;
    }

    pFileReport = fopen("traces.csv", "w");
    for (std::vector<LttngTraceRecord>::iterator it = vec_ltr.begin(); it != vec_ltr.end(); it++) {
        fprintf(pFileReport, "%5.9lf,%d,%s\n", (*it).timestamp, kf_map[(*it).kf_name], (*it).kf_name.c_str());
    }

    fclose(pFileReport);
    return 0;
}
