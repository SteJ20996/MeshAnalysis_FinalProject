#include "manip.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>
// you will need cmath and algorithm headers.

namespace ams562_final {

void compute_n2e_adj(const unsigned n, const Triangles &conn,
                     std::vector<std::vector<int>> &adj) {
  // resize adj to n
  adj.resize(n);
  // reserve for each of them with a reasonable upper bound

  // your code
  int idx = 0;
  std::for_each(conn.to_vector().begin(),conn.to_vector().end(),[&](const std::array<int,3> &x ){
    adj[x[0]].push_back(idx);
    adj[x[1]].push_back(idx);
    adj[x[2]].push_back(idx);
    idx++;
  }
  );
}

void compute_avg_normals(const SphCo &points, const Triangles &conn,
                         const std::vector<std::vector<int>> &n2e_adj,
                         SphCo &nrms) {
  // resize the nrms
  nrms.resize(points.npoints());

  // your code
  for(int i = 0; i < points.npoints(); i++){
    int subsize = n2e_adj[i].size();
    for(int j = 0; j < subsize; j++){
       int x = conn[n2e_adj[i][j]][0];
       int y = conn[n2e_adj[i][j]][1];
       int z = conn[n2e_adj[i][j]][2];

       std::vector<double> v1(3,0.0);
       std::vector<double> v2(3,0.0);
       std::vector<double> v3(3,0.0);

       for(int k = 0; k < 3; k++){
         v1[k] = points[y][k] - points[x][k];
         v2[k] = points[z][k] - points[x][k];
       }

       v3[0] = v1[1]*v2[2]-v1[2]*v2[1];
       v3[1] = -v1[0]*v2[2] + v1[2]*v2[0];
       v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
       double norm = sqrt(v3[0]*v3[0]+v3[1]*v3[1]+v3[2]*v3[2]);

       for(int k = 0; k < 3; k++){
            v3[k] = v3[k] / norm;
            nrms[i][k] += v3[k]/subsize;
       }
       }
  }
  // hint don't forget normalizing the normals
  nrms.normalize();
}

void compute_errors(const SphCo &exact, const SphCo &num,
                    std::vector<double> &acos_theta) {
  // resize the error array
  acos_theta.resize(num.npoints());

  // your code
  std::vector<std::array<double,6> > comb(num.npoints());
  int idx = 0;
  for(int i = 0; i < num.npoints(); i++){
    comb[i][0] = exact[i][0];
    comb[i][1] = exact[i][1];
    comb[i][2] = exact[i][2];
    comb[i][3] = num[i][0];
    comb[i][4] = num[i][1];
    comb[i][5] = num[i][2];
  }
  std::for_each(comb.begin(),comb.end(),[&](const std::array<double,6> &x){
    double dot = (x[0]*x[3]) + (x[1]*x[4]) + (x[2]*x[5]);
    acos_theta[idx] = acos(dot);
    idx ++;
  }
  );
}

}  // namespace ams562_final

int main(){
    int n = 10;
    std::vector< std::vector<int> > x(n);
    std::cout << x.size() << std::endl;
    for(int idx = 0; idx < n; idx++){
        x[idx].push_back(idx);
        std::cout << x[idx].size() << std::endl;
    }
}