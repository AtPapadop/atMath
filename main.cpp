#include "Vector.cpp"
#include <cstdint>
#include <vector>

using namespace atMath;
using std::cout, std::endl;

int main(){
    std::vector<double> v1 = {1.1, 2.2, 3.3, 4.4};

    Vector vec1(v1);
    Vector vec2 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    Vector<int> vec3 = {1, 2, 3, 4, 5};
    cout << vec1 << endl;
    cout << vec2 << endl;
    cout << vec3 << endl;

    Vector vec = vec3 + vec2;

    vec+=vec2;

    cout << vec << endl;

    vec+=vec2;
    cout << vec << endl;
    cout << vec2 << endl;
    cout << vec1 << endl;

    vec3*=2.8;
    cout << vec3 << endl;

    Vector vec4 = vec2.inverse();
    Vector vec5 = vec2.normalize();

    cout << vec4 << endl;
    cout << vec5 << endl;

    vec3.append(11.2f);
    cout << vec3 << endl;

    vec3.insert(2, 11.2f);
    cout << vec3 << endl;

    vec3.append(vec2);
    cout << vec3 << endl;

    vec3.insert(2, vec2);
    cout << vec3 << endl;

    vec3.resize(5);
    cout << vec3 << endl;



    cout << vec3.dot(vec2) << endl;

    float dot_product = static_cast<float>(vec3.dot(vec2));
    cout << dot_product << endl;

    vec3.resize(3);
    vec2.resize(3);
    Vector vec6 = vec3^vec2;
    cout << vec6 << endl;
    vec2*=2.1f;
    cout << vec2 << endl;
    //vec3 = vec3.inverse();
    //cout << vec3 << endl;

    vec2 = vec3.normalize();


    cout << vec3 << endl;
    cout << vec2 << endl;

    auto vec23 = vec2 * vec3;
    vec2*=vec3;
    cout << vec2 << endl;
    cout << vec23 << endl;
    return 0;
}