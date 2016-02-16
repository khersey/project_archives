package dialogc;

/**
 * Created by kyle on 15-02-12.
 * This class stores settings information.
 */
public class Settings {
    private String filename;
    private String filepath;
    private String workingDir;
    private String compiler;
    private String compilerArgs;
    private String JVM;
    private String JVMArgs;
    private boolean useYadc;

    public Settings() {
        filename = "untitled";
        filepath = "/";
        workingDir = ".";
        compiler = "javac";
        compilerArgs = "-classpath";
        JVM = "java";
        JVMArgs = "-classpath";
        useYadc = false;
    }

    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename.substring(0,filename.length() - 7); //remove .config from filename
    }

    public String getFilepath() {
        return filepath;
    }

    public void setFilepath(String filepath) {
        this.filepath = filepath;
    }

    public String getWorkingDir() {
        return workingDir;
    }

    public void setWorkingDir(String workingDir) {
        this.workingDir = workingDir;
    }

    public String getCompiler() {
        return compiler;
    }

    public void setCompiler(String compiler) {
        this.compiler = compiler;
    }

    public String getCompilerArgs() {
        return compilerArgs;
    }

    public void setCompilerArgs(String compilerArgs) {
        this.compilerArgs = compilerArgs;
    }

    public String getJVM() {
        return JVM;
    }

    public void setJVM(String JVM) {
        this.JVM = JVM;
    }

    public String getJVMArgs() {
        return JVMArgs;
    }

    public void setJVMArgs(String JVMArgs) {
        this.JVMArgs = JVMArgs;
    }

    public boolean getUseYadc() {
        return useYadc;
    }

    public void setUseYadc(boolean useYadc) {
        this.useYadc = useYadc;
    }
}
