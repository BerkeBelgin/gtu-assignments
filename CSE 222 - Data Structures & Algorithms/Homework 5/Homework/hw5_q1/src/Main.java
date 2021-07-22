public class Main {
	public static void print(String str) {
		System.out.print(str);
	}
	
	public static void main(String[] args) {
		FileSystemTree myFileSystem = new FileSystemTree("root");
		myFileSystem.addDir("root/first_directory");
		myFileSystem.addDir("root/second_directory");
		myFileSystem.addDir("root/third_directory");
		myFileSystem.addDir("root/file.txt");
		myFileSystem.addFile("root/first_directory/new_file.txt");
		myFileSystem.addFile("root/first_directory/new_file2.txt");
		myFileSystem.addDir("root/second_directory/new_directory");
		myFileSystem.addDir("root/second_directory/new_directory2");
		myFileSystem.addDir("root/second_directory/new_directory3");
		myFileSystem.addFile("root/second_directory/new_directory/new_file.doc");
		myFileSystem.addFile("root/second_directory/new_directory/new_file2.doc");
		print("\nHierarchy created\n");
		myFileSystem.printFileSystem();
		print("\nSearching files and folders that contain \"new\" in their names.\n");
		myFileSystem.search("new");
		print("\nRemoving \"root/first_directory/new_file.txt\"\n");
		myFileSystem.remove("root/first_directory/new_file.txt");
		print("\nRemoving \"root/second_directory/new_directory\"\n");
		myFileSystem.remove("root/second_directory/new_directory");
		myFileSystem.printFileSystem();

	}
}
