#ifndef PROYECTO_MINMATCH_H
#define PROYECTO_MINMATCH_H

using namespace std;

class MinMatch {
private:
    vector<int> A;
    vector<int> B;
    vector<int> pesosA;
    vector<int> pesosB;
    vector< pair<int, int> > rangosA;
    vector< pair<int, int> > rangosB;

public:

    MinMatch(const vector<int>& _A, const vector<int>& _B) {
        for (int i : _A) {
            A.push_back(i);
        }

        for (int i : _B) {
            B.push_back(i);
        }

        setPesosYRangos();

        for (int i : pesosA) {
            cout << i << " ";
        }

        cout << endl;

        for (int i : pesosB) {
            cout << i << " ";
        }

        cout << "\n" << endl;

        for (pair<int, int> i : rangosA) {
            cout << i.first << " " << i.second << endl;
        }

        for (pair<int, int> i : rangosB) {
            cout << i.first << " " << i.second << endl;
        }
    }

    ///Metodos importantes




    //Destructor
    ~MinMatch() = default;

private:
    ///Metodos de apoyo
    void setPesosYRangos() {
        int temp = 0;
        bool enabled = false;
        int i;
        int x, y;
        pair<int, int> aux;

        for (i = 0; i < A.size(); ++i) {
            if (A[i] == 1) {
                if (!enabled) {
                    x = i;
                }
                enabled = true;
                ++temp;
                if (i == A.size() - 1) {
                    pesosA.push_back(temp);
                    aux = make_pair(x, i);
                    rangosA.push_back(aux);
                }

            } else if (enabled) {
                y = i-1;
                enabled = false;
                pesosA.push_back(temp);
                temp = 0;
                aux = make_pair(x, y);
                rangosA.push_back(aux);
            }
        }

        enabled = false;
        temp = 0;
        for (i = 0; i < B.size(); ++i) {
            if (B[i] == 1) {
                if (!enabled) {
                    x = i;
                }
                enabled = true;
                ++temp;
                if (i == B.size() - 1) {
                    pesosB.push_back(temp);
                    aux = make_pair(x, i);
                    rangosB.push_back(aux);
                }

            } else if (enabled) {
                y = i-1;
                enabled = false;
                pesosB.push_back(temp);
                temp = 0;
                aux = make_pair(x, y);
                rangosB.push_back(aux);
            }
        }
    }
};


#endif //PROYECTO_MINMATCH_H
