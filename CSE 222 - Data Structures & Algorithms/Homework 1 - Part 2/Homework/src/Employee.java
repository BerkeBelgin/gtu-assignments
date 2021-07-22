

/**
 * Employee interface for Branch Employee and Transport Personnel to implement
 * @author Berke Belgin
 * @version 1.0
 * @since 2020-03-03
 */
public interface Employee {
	String toString();
	void updateShipmentStatus(int shipmentId, int status) throws Exception;
}
