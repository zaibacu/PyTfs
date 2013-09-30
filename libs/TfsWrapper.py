from ctypes import *

class TfsTask(Structure):
	_fields_ = [
		("title", c_char_p),
		("description", c_char_p),
		("id", c_long)
	]

class TfsTaskList(Structure):
	pass

TfsTaskList._fields_ = [
		("task", TfsTask),
		("next", POINTER(TfsTaskList))
	]
	

class TfsWrapper(object):
	def __init__(self):
		self.lib = cdll.LoadLibrary("PyUtil.dll")

	def connect(self, url, collection):
		self.lib.ConnectToTfs.restype = c_bool
		self.lib.ConnectToTfs.argtype = [c_char_p, c_char_p]
		return self.lib.ConnectToTfs(url, collection)

	def query(self, query):
		self.lib.QueryTfs.restype = POINTER(TfsTaskList)
		self.lib.QueryTfs.argtype = [c_char_p]
		result = self.lib.QueryTfs(query)
		task_list = result;
		tasks = []
		while bool(task_list) != False:
			data = task_list.contents
			tasks.append(data.task)
			task_list = data.next

		tasks.pop() #Remove last element, since it is a nullptr
		return tasks