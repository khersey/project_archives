package dialogc;

/**
 * Created by kyle on 15-02-10.
 * This class makes use of the Parameter Manager C library to parse data from a config file.
 */
public class PM_Parser {
    private String title;
    private String[] fieldNames;
    private String[] fieldValues;
    private String[] buttonNames;
    private String[] buttonValues;
    private boolean success;

    public final static String dir = System.getProperty("user.dir");

    static { System.load(dir + "/lib/libJNIpm.so"); }


    public PM_Parser(String filepath) {
        success = true;
        try {
            title = parseTitle(filepath);
            fieldNames = parseFields(filepath);
            if(fieldNames.length > 0) {
                fieldValues = parseValues(filepath, fieldNames);
            }
            buttonNames = parseButtons(filepath);
            if(buttonNames.length > 0) {
                buttonValues = parseValues(filepath, buttonNames);
            }

        } catch (Exception e) {
            success = false;
        }

    }

    public boolean isSuccess() {
        return success;
    }

    public void setSuccess(boolean success) {
        this.success = success;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String[] getFieldName() {
        return fieldNames;
    }

    public void setFieldName(String[] fieldName) {
        this.fieldNames = fieldName;
    }

    public String[] getFieldValue() {
        return fieldValues;
    }

    public void setFieldValue(String[] fieldValue) {
        this.fieldValues = fieldValue;
    }

    public String[] getButtonName() {
        return buttonNames;
    }

    public void setButtonName(String[] buttonName) {
        this.buttonNames = buttonName;
    }

    public String[] getButtonValue() {
        return buttonValues;
    }

    public void setButtonValue(String[] buttonValue) {
        this.buttonValues = buttonValue;
    }

    native private String parseTitle(String filepath) throws Exception;
    native private String[] parseFields(String filepath) throws Exception;
    native private String[] parseButtons(String filepath) throws Exception;
    native private String[] parseValues(String filepath, String[] fields) throws Exception;

}
