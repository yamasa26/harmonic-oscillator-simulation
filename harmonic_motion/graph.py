import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('simulation.csv')
plt.figure(figsize=(14, 5))

#変位の比較
plt.subplot(1, 2, 1)
plt.plot(df['time'], df['x_eu'], label='Euler', linestyle='--', alpha=0.7)
plt.plot(df['time'], df['x_rk'], label='RK4', linewidth=1, alpha=0.9)
plt.title('Displacement: Euler vs RK4')
plt.xlabel('Time [s]')
plt.ylabel('Position [m]')
plt.legend()
plt.grid(True)

#エネルギーの比較
plt.subplot(1, 2, 2)
plt.plot(df['time'], df['e_eu'], label='Euler Energy')
plt.plot(df['time'], df['e_rk'], label='RK4 Energy')
plt.title('Total Energy Conservation')
plt.xlabel('Time [s]')
plt.ylabel('Energy [J]')
plt.legend()
plt.grid(True)

#相空間の比較
plt.figure(figsize=(8, 8)) 
plt.plot(df['x_rk'], df['v_rk'], label='RK4 (Stable)', color='black', linewidth=1, alpha=0.5)
plt.plot(df['x_eu'], df['v_eu'], label='Euler (Energy Gain)', color='red', linewidth=1.5, alpha=0.8)

plt.title('Phase Space Comparison: Spiraling Out in Euler Method')
plt.xlabel('Position [m]')
plt.ylabel('Velocity [m/s]')
plt.axis('equal') 

plt.legend()
plt.grid(True, linestyle=':')
plt.savefig('phase_space.png')

plt.tight_layout()
plt.show()