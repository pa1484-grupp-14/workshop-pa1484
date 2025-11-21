from os.path import isfile
Import("env")
assert isfile(".env")
try:
  f = open(".env", "r")
  lines = f.readlines()
  envs = []
  for line in lines:
    line = line.strip().split("=")
    variable = line[0]
    content = "=".join(line[1:])
    envs.append("-D{}=\\\"{}\\\"".format(variable.strip(), content.strip()))
  env.Append(BUILD_FLAGS=envs)
except IOError:
  print("File .env not accessible",)
finally:
  f.close()
