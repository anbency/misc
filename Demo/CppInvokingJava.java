public class CppInvokingJava{  
    
    public CppInvokingJava(){
        super();
    }
    /*
    public static void main(String[] args){  
  
        String path = System.getProperty("java.library.path");  
        System.out.println(path);  
    }
    */
    public static int add(int a,int b) {
        return a+b;
    }
    public boolean judge(boolean bool) {
        return !bool;
    }
}  