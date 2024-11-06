import math

# define require parameter 
α_pass = -1
α_stop = -12
ω_pass = 1
ω_stop = 2
m = 0

def calculate_n(α_stop, α_pass, ω_stop, ω_pass): 
  orde_filter = math.log10((10 ** (-0.1 * α_stop) - 1) / (10 ** (-0.1 * α_pass) - 1)) / (2 * (math.log10(ω_stop / ω_pass)))
  
  result = math.ceil(orde_filter)
  return result

def calculate_ε(α_pass):
  ε = (10 ** (-0.1 * α_pass) - 1) ** (1 / 2)
  
  result = round(ε, 4)
  return result

def calculate_R(ε, n):
  R = ε ** (-1 / n)
  
  result = round(R, 4)
  return result

def calculate_θ(m, n): 
  θ = (math.pi * ((2 * m) + n + 1)) / (2 * n)
  degree = math.degrees(θ)
  
  result = math.ceil(degree)
  return result

def calculate_σm(R, θ):
  radian = math.radians(θ)
  σm = R * math.cos(radian)
  
  result = round(σm, 4)
  return result

def calculate_ωm(R, θ):
  radian = math.radians(θ)
  ωm = R * math.sin(radian)
  
  result = round(ωm, 4)
  return result

def calculate_σR(R):
  result = -R
  return result

def calculate_B1m(σ0):
  result = -2 * σ0
  return result

def calculate_B2m(σm, ωm):
  B2m = (σm ** 2) + (ωm ** 2)
  
  result = round(B2m, 4)
  return result

def HB3S(B1m_value, B2m_value):
  print(f"                     B1 . B2")
  print(" HB,3(S) =  ---------------------------")
  print("            (S + B1) (S² + B1 . S + B2) \n")
  print(f"                      ({B1m_value[0]}) . ({B2m_value[0]})")
  print("         =  --------------------------------------")
  print(f"            (S + {B1m_value[0]}) (S² + {B1m_value[0]} . S + {B2m_value[0]})")

def HB4S(B1m_value, B2m_value):
  print("                            B2,0 . B2,1")
  print(" HB,4(S) =  ---------------------------------------------")
  print("            (S² + B1,0 . S + B2,0) (S² + B1,1 . S + B2,1) \n")
  print(f"                     ({B2m_value[0]}) . ({B2m_value[1]})")
  print("         =  -----------------------------------------------------")
  print(f"            (S² + {B1m_value[0]} . S + {B2m_value[0]}) (S² + {B1m_value[1]} . S + {B2m_value[1]})") 
  

# inisialitation variable
θ_value = []
σm_value = []
ωm_value = []
B1m_value = []
B2m_value = []

# not to custom
n = calculate_n(α_stop, α_pass, ω_stop, ω_pass)
ε = calculate_ε(α_pass)
R = calculate_R(ε, n)
θ = calculate_θ(m, n)

σR = calculate_σR(R)

for i in range(m + 1):
  θ_value.append(calculate_θ(i, n))
  σm_value.append(calculate_σm(R, θ_value[i]))
  ωm_value.append(calculate_ωm(R, θ_value[i]))
  B1m_value.append(calculate_B1m(σm_value[i]))
  B2m_value.append(calculate_B2m(σm_value[i], ωm_value[i]))
  
print("\n\n==================================================================")
print("----------- Hasil Perhitungan Normalized Approximation -----------")
print("==================================================================\n")

print("Nilai n      : ", n)
print("Nilai ε      : ", ε)
print("Nilai R      : ", R)

print("")

for i in range(m + 1):
  print(f"Nilai θ_{i}    :  {θ_value[i]}°")

for i in range(m + 1):
  print(f"Nilai σm_{i}   :  {σm_value[i]}")
  
for i in range(m + 1):
  print(f"Nilai ωm_{i}   :  {ωm_value[i]}")

print("")
  
for i in range(m + 1):
  print(f"Nilai B1m_{i}  :  {B1m_value[i]}")
  
for i in range(m + 1):
  print(f"Nilai B2m_{i}  :  {B2m_value[i]}")
  
print("")

print("Transfer Functionnya adalah: \n")

if (m == 0):
  HB3S(B1m_value, B2m_value)
elif (m == 1):
  HB4S(B1m_value, B2m_value)

print("\n==================================================================")
print("---------------------- Perhitungan Selesai -----------------------")
print("==================================================================\n\n")