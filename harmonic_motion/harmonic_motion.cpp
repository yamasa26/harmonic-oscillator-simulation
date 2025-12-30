#include<iostream>
#include<string>
#include<cmath>
#include <iomanip> 
#include <fstream>

double k = 20.0;    //ばね定数[N/m]
double m = 0.5;     //質量[kg]
double x0 = 0.1;    //初期変位[m]
double v0 = 0.0;    //初期速度[m/s]
double a0;          //初期加速度[m/s^2]
double dt = 0.05;  //時間刻み[s]
double t = 0;       //現在時間[s]
double t_max = 10;  //シミュレーション時間[s]

// エネルギーの計算
double get_energy(double x, double v) {
    return 0.5 * m * v * v + 0.5 * k * x * x;
}

//加速度の計算
double get_acceleration(double x){
    return -( k / m ) * x; 
}

//RK4の計算
void step_rk4(double &x_rk, double &v_rk, double dt){
    //k1：現時点の勾配
    double k1_x = v_rk;
    double k1_v = get_acceleration(x_rk);
    //k2：k1を使ってdt/2進んだ勾配
    double k2_x = v_rk + k1_v * (dt / 2.0);
    double k2_v = get_acceleration(x_rk + k1_x * dt/2.0);
    //k3：k2を使ってdt/2進んだ勾配
    double k3_x = v_rk + k2_v * (dt / 2.0);
    double k3_v = get_acceleration(x_rk + k2_x * dt/2.0); 
    //k4：k3を使ってdt進んだ勾配
    double k4_x = v_rk + k3_v * dt;
    double k4_v = get_acceleration(x_rk + k3_x * dt);
    //重み付き平均
    x_rk += (k1_x + 2*k2_x + 2*k3_x + k4_x) * dt / 6;
    v_rk += (k1_v + 2*k2_v + 2*k3_v + k4_v) * dt / 6;
}

int main(){
    //オイラー法の変数
    double x_eu = x0, v_eu = v0;
    //RK4の変数
    double x_rk = x0, v_rk = v0;

    std::ofstream ofs("simulation.csv");
    if (!ofs) {
        std::cerr << "this file cannot be open" << std::endl;
        return 1;
    }

    ofs << "time,x_eu,v_eu,e_eu,x_rk,v_rk,e_rk" << std::endl;

    while(t <= t_max){
        ofs << t << "," 
            << x_eu << "," << v_eu << "," << get_energy(x_eu, v_eu) << ","
            << x_rk << "," << v_rk << "," << get_energy(x_rk, v_rk) << std::endl;

        // オイラー法
        double a_eu = get_acceleration(x_eu);
        v_eu += a_eu * dt;
        x_eu += v_eu * dt;
        
        // RK4
        step_rk4(x_rk, v_rk, dt);

        t += dt;
    }

    std::cout << "Simulation finished. Saved to simulation.csv" << std::endl;
    return 0;
}
