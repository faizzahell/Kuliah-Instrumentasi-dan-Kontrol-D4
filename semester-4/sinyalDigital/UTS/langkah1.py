import math

def calculate_epsilon(a_pass):
  """
  This function calculates epsilon based on the equation in the image.

  Args:
      a_pass: The value of a_pass.

  Returns:
      The calculated epsilon value.
  """

  epsilon = math.sqrt(10 ** (-0.1 * a_pass))
  return epsilon

# Example usage
a_pass = -1
epsilon = calculate_epsilon(a_pass)
print("Epsilon:", epsilon)