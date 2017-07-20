import java.lang.reflect.Field;  
import java.io.IOException;

public class HelloNativeTest {
    public static void addLibraryDir(String libraryPath) throws IOException {  
        try {  
            Field field = ClassLoader.class.getDeclaredField("usr_paths");  
            field.setAccessible(true);  
            String[] paths = (String[]) field.get(null);  
            for (int i = 0; i < paths.length; i++) {  
                if (libraryPath.equals(paths[i])) {
                    System.out.println("paths had been included");
                    return;  
                }  
            }  
  
            String[] tmp = new String[paths.length + 1];  
            System.arraycopy(paths, 0, tmp, 0, paths.length);  
            tmp[paths.length] = libraryPath;  
            field.set(null, tmp);
        } catch (IllegalAccessException e) {  
            throw new IOException(  
                    "Failedto get permissions to set library path");  
        } catch (NoSuchFieldException e) {  
            throw new IOException(  
                    "Failedto get field handle to set library path");  
        } catch(Exception e){ 
            throw new IOException(  
                    "Failedto others to set library path");  
        }
        
    }  
    static {
            
                try {
                        System.out.println(System.getProperty("java.library.path"));
                        addLibraryDir("D:\\test\\Demo\\HelloJni\\Debug"); //it is ok by this way "method-c"
                        //it is ok by this way "method-a"
                        /*
                        System.setProperty("java.library.path", System.getProperty("java.library.path")
                        + ";D:\\test\\Demo\\HelloJni\\Debug");
                        Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
                        fieldSysPath.setAccessible(true);
                        fieldSysPath.set(null, null);
                        */
                        //it is ok by this way "method-a"
                        System.out.println(System.getProperty("java.library.path"));
                        System.loadLibrary("HelloJni");
                        //System.load("D:\\test\\Demo\\HelloJni\\Debug\\HelloJni.dll");  //it is ok by this way "method-b"
                } catch (Exception e) {
                        System.out.println(e);
                        System.out.println("load dll fail");
                // do nothing for exception
                }
            
            //    System.loadLibrary("HelloJni");
    }

    public native void greeting();

    public static void main(String[] args) {
        new HelloNativeTest().greeting();
    }
}