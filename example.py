from libs.TfsWrapper import *

tfs = TfsWrapper()

tfs.connect(b"http://tfsserver.com", "Project")

print(tfs.query("""
   Select [State], [Title] 
   From WorkItems
   Where [Work Item Type] = 'User Story'
   Order By [State] Asc, [Changed Date] Desc
"""))