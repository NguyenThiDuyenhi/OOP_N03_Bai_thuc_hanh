#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
using namespace std;
class Vehicle {
private:
	int vehicleID;
	string vehicleType;
	int entryTime;
	int parkingDuration;
	double parkingFee;
	bool isOccupied;
public:
	Vehicle() {
		vehicleID = 0;
		vehicleType = "";
		entryTime = 0;
		parkingDuration = 0;
		parkingFee = 0;
		isOccupied = false;
	}
	Vehicle(int id, string type, int time, int duration,
		double fee, bool occupied) {
		vehicleID = id;
		setLoaiXe(type);
		entryTime = time;
		parkingDuration = duration;
		parkingFee = fee;
		isOccupied = occupied;
	}
	int getMaXe() const { return vehicleID; }
	string getLoaiXe() const { return vehicleType; }
	int getGioVao() const { return entryTime; }
	int getThoiGianDo() const { return parkingDuration; }
	double getPhi() const { return parkingFee; }
	bool getDaCoXe() const { return isOccupied; }
	void setMaXe(int id) { vehicleID = id; }
	void setLoaiXe(string type) {
		for (int i = 0; i < (int)type.length(); i++) {
			type[i] = tolower(type[i]);
		}
		if (type == "car") {
			vehicleType = "Car";
		}
		else if (type == "motorcycle") {
			vehicleType = "Motorcycle";
		}
		else if (type == "bicycle") {
			vehicleType = "Bicycle";
		}
		else {
			vehicleType = "";
		}
	}
	void setGioVao(int time) { entryTime = time; }
	void setThoiGianDo(int duration) { parkingDuration = duration; }
	void setPhi(double fee) { parkingFee = fee; }
	void setDaCoXe(bool occupied) { isOccupied = occupied; }
	void tinhPhi() {
		double rate = 0;
		if (vehicleType == "Car") 
			rate = 6;
		else if (vehicleType == "Motorcycle") 
			rate = 4;
		else if (vehicleType == "Bicycle")
			rate = 2;

		bool isPeak = false;
		if ((entryTime >= 6 && entryTime < 10) || (entryTime >= 15 && entryTime < 19))
			isPeak = true;
		double donGiaHaiGioDau;
		if (isPeak) 
			donGiaHaiGioDau = rate * 1.3;
		else 
			donGiaHaiGioDau = rate * 0.95;
		
		int soGioDau = parkingDuration;
		if (soGioDau > 2) 
			soGioDau = 2;

		parkingFee = soGioDau * donGiaHaiGioDau;
		if (parkingDuration > 2) {
			int soGioConLai = parkingDuration - 2;
			parkingFee = parkingFee + soGioConLai * rate * 0.9;
		}
	}
	void hienThi() const {
		cout << "Ma xe: " << vehicleID << endl;
		cout << "Loai xe: " << vehicleType << endl;
		cout << "Gio vao: " << entryTime << endl;
		cout << "So gio do: " << parkingDuration << endl;
		cout << "Phi do xe: " << parkingFee << " VND" << endl;
	}
};
class ParkingLot {
private:
	int parkID;
	char size;
	Vehicle vehicle1, vehicle2, vehicle3;
	bool hasVehicle1, hasVehicle2, hasVehicle3;
public:
	ParkingLot() {
		parkID = 0;
		size = 'S';
		hasVehicle1 = false;
		hasVehicle2 = false;
		hasVehicle3 = false;
	}
	ParkingLot(int id, char s) {
		parkID = id;
		size = toupper(s);
		hasVehicle1 = false;
		hasVehicle2 = false;
		hasVehicle3 = false;
	}
	int getMaBai() const { return parkID; }
	char getKichThuoc() const { return size; }

	bool coXeTaiViTri(int viTri) const {
		if (viTri == 1) return hasVehicle1;
		if (viTri == 2) return hasVehicle2;
		if (viTri == 3) return hasVehicle3;
		return false;
	}
	Vehicle layXeTaiViTri(int viTri) const {
		if (viTri == 1) return vehicle1;
		if (viTri == 2) return vehicle2;
		if (viTri == 3) return vehicle3;
		return Vehicle();
	}
	int demXe() const {
		int dem = 0;
		if (hasVehicle1) dem++;
		if (hasVehicle2) dem++;
		if (hasVehicle3) dem++;
		return dem;
	}
	bool themXe(const Vehicle& v) {
		Vehicle xeMoi = v;
		xeMoi.setDaCoXe(true);
		if (!hasVehicle1) {
			vehicle1 = xeMoi;
			hasVehicle1 = true;
			return true;
		}
		if (size == 'M' || size == 'L') {
			if (!hasVehicle2) {
				vehicle2 = xeMoi;
				hasVehicle2 = true;
				return true;
			}
		}
		if (size == 'L') {
			if (!hasVehicle3) {
				vehicle3 = xeMoi;
				hasVehicle3 = true;
				return true;
			}
		}
		return false;
	}
	bool xoaXe(int vID) {
		if (hasVehicle1 && vehicle1.getMaXe() == vID) {
			vehicle1 = Vehicle();
			hasVehicle1 = false;
			return true;
		}
		if (hasVehicle2 && vehicle2.getMaXe() == vID) {
			vehicle2 = Vehicle();
			hasVehicle2 = false;
			return true;
		}
		if (hasVehicle3 && vehicle3.getMaXe() == vID) {
			vehicle3 = Vehicle();
			hasVehicle3 = false;
			return true;
		}
		return false;
	}
	void hienThiThongTinBai() const {
		cout << "\n--------------------------\n";
		cout << "Ma bai do: " << parkID << endl;
		cout << "Kich thuoc: " << size << endl;
		cout << "So xe hien co: " << demXe() << endl;
		if (hasVehicle1) {
			cout << "\nXe tai vi tri 1:\n";
			vehicle1.hienThi();
		}
		if (hasVehicle2) {
			cout << "\nXe tai vi tri 2:\n";
			vehicle2.hienThi();
		}
		if (hasVehicle3) {
			cout << "\nXe tai vi tri 3:\n";
			vehicle3.hienThi();
		}
	}
};
class SystemInterface {
private:
	ParkingLot parkingLot1, parkingLot2, parkingLot3;
	bool hasLot1, hasLot2, hasLot3;
	int nhapSoNguyen(string loiNhac) {
		int giaTri;
		cout << loiNhac;
		while (!(cin >> giaTri)) {
			cout << "Du lieu khong hop le. Nhap lai: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		return giaTri;
	}
	string nhapChuoi(string loiNhac) {
		string giaTri;
		cout << loiNhac;
		cin >> giaTri;
		return giaTri;
	}
	bool maBaiDaTonTai(int id) const {
		if (hasLot1 && parkingLot1.getMaBai() == id) return true;
		if (hasLot2 && parkingLot2.getMaBai() == id) return true;
		if (hasLot3 && parkingLot3.getMaBai() == id) return true;
		return false;
	}
	bool baiCoXe(const ParkingLot& bai, int maXe) const {
		for (int i = 1; i <= 3; i++) {
			if (bai.coXeTaiViTri(i) && bai.layXeTaiViTri(i).getMaXe() == maXe) {
				return true;
			}
		}
		return false;
	}
	bool maXeDaTonTai(int maXe) const {
		if (hasLot1 && baiCoXe(parkingLot1, maXe)) return true;
		if (hasLot2 && baiCoXe(parkingLot2, maXe)) return true;
		if (hasLot3 && baiCoXe(parkingLot3, maXe)) return true;
		return false;
	}
	void congDonPhi(const ParkingLot& bai, string loai,
		double& tong, int& dem) const {
		for (int i = 1; i <= 3; i++) {
			if (bai.coXeTaiViTri(i)) {
				Vehicle v = bai.layXeTaiViTri(i);
				if (v.getLoaiXe() == loai) {
					tong = tong + v.getPhi();
					dem++;
				}
			}
		}
	}
	int inXeTheoLoai(const ParkingLot& bai, string loai) const {
		int soXeDaIn = 0;
		for (int i = 1; i <= 3; i++) {
			if (bai.coXeTaiViTri(i)) {
				Vehicle v = bai.layXeTaiViTri(i);
				if (v.getLoaiXe() == loai) {
					cout << "\nBai do: " << bai.getMaBai() << endl;
					v.hienThi();
					soXeDaIn++;
				}
			}
		}
		return soXeDaIn;
	}
	void inTrungBinh(string loai, double tong, int dem) const {
		cout << loai << ": ";
		if (dem > 0) {
			cout << tong / dem << " VND" << endl;
		}
		else {
			cout << "Chua co xe" << endl;
		}
	}
	void baoCaoToanHe(string loai) const {
		double tong = 0;
		int dem = 0;
		if (hasLot1) congDonPhi(parkingLot1, loai, tong, dem);
		if (hasLot2) congDonPhi(parkingLot2, loai, tong, dem);
		if (hasLot3) congDonPhi(parkingLot3, loai, tong, dem);
		inTrungBinh(loai, tong, dem);
	}
	void baoCaoMotLoaiTrongBai(const ParkingLot& bai, string loai) const {
		double tong = 0;
		int dem = 0;
		congDonPhi(bai, loai, tong, dem);
		inTrungBinh(loai, tong, dem);
	}
	void baoCaoMotBai(const ParkingLot& bai) const {
		cout << "\nBai do " << bai.getMaBai() << endl;
		baoCaoMotLoaiTrongBai(bai, "Car");
		baoCaoMotLoaiTrongBai(bai, "Motorcycle");
		baoCaoMotLoaiTrongBai(bai, "Bicycle");
	}
	void taoBaiDo() {
		if (hasLot1 && hasLot2 && hasLot3) {
			cout << "He thong da du 3 bai do!\n";
			return;
		}
		int id = nhapSoNguyen("Nhap ma bai do: ");
		if (maBaiDaTonTai(id)) {
			cout << "Ma bai do da ton tai!\n";
			return;
		}
		char s;
		cout << "Nhap kich thuoc (S/M/L): ";
		cin >> s;
		s = toupper(s);
		if (s != 'S' && s != 'M' && s != 'L') {
			cout << "Kich thuoc khong hop le!\n";
			return;
		}
		if (!hasLot1) {
			parkingLot1 = ParkingLot(id, s);
			hasLot1 = true;
		}
		else if (!hasLot2) {
			parkingLot2 = ParkingLot(id, s);
			hasLot2 = true;
		}
		else {
			parkingLot3 = ParkingLot(id, s);
			hasLot3 = true;
		}
		cout << "Tao bai do thanh cong!\n";
	}
	void themXeVaoHeThong() {
		if (!hasLot1 && !hasLot2 && !hasLot3) {
			cout << "Chua co bai do nao!\n";
			return;
		}
		int id = nhapSoNguyen("Nhap ma xe: ");
		if (maXeDaTonTai(id)) {
			cout << "Ma xe da ton tai!\n";
			return;
		}
		string loai = nhapChuoi("Nhap loai xe (Car/Motorcycle/Bicycle): ");
		Vehicle v;
		v.setLoaiXe(loai);
		if (v.getLoaiXe() == "") {
			cout << "Loai xe khong hop le!\n";
			return;
		}
		int gioVao = nhapSoNguyen("Nhap gio vao (0-23): ");
		if (gioVao < 0 || gioVao > 23) {
			cout << "Gio vao khong hop le!\n";
			return;
		}
		int thoiGianDo = nhapSoNguyen("Nhap so gio do (1-23): ");
		if (thoiGianDo < 1 || thoiGianDo > 23) {
			cout << "Thoi gian do khong hop le!\n";
			return;
		}
		v.setMaXe(id);
		v.setGioVao(gioVao);
		v.setThoiGianDo(thoiGianDo);
		v.setDaCoXe(true);
		v.tinhPhi();
		if (hasLot1 && parkingLot1.themXe(v)) {
			cout << "Them xe vao bai " << parkingLot1.getMaBai() << " thanh cong!\n";
			cout << "Phi do xe: " << v.getPhi() << " VND\n";
			return;
		}
		if (hasLot2 && parkingLot2.themXe(v)) {
			cout << "Them xe vao bai " << parkingLot2.getMaBai() << " thanh cong!\n";
			cout << "Phi do xe: " << v.getPhi() << " VND\n";
			return;
		}
		if (hasLot3 && parkingLot3.themXe(v)) {
			cout << "Them xe vao bai " << parkingLot3.getMaBai() << " thanh cong!\n";
			cout << "Phi do xe: " << v.getPhi() << " VND\n";
			return;
		}
		cout << "Tat ca cac bai do da day!\n";
	}
	void xoaBaiDo() {
		int id = nhapSoNguyen("Nhap ma bai do can xoa: ");
		if (hasLot1 && parkingLot1.getMaBai() == id) {
			parkingLot1 = ParkingLot();
			hasLot1 = false;
			cout << "Da xoa bai do!\n";
			return;
		}
		if (hasLot2 && parkingLot2.getMaBai() == id) {
			parkingLot2 = ParkingLot();
			hasLot2 = false;
			cout << "Da xoa bai do!\n";
			return;
		}
		if (hasLot3 && parkingLot3.getMaBai() == id) {
			parkingLot3 = ParkingLot();
			hasLot3 = false;
			cout << "Da xoa bai do!\n";
			return;
		}
		cout << "Khong tim thay bai do!\n";
	}
	void layXeRa() {
		int id = nhapSoNguyen("Nhap ma xe can lay ra: ");
		if (hasLot1 && parkingLot1.xoaXe(id)) {
			cout << "Lay xe thanh cong!\n";
			return;
		}
		if (hasLot2 && parkingLot2.xoaXe(id)) {
			cout << "Lay xe thanh cong!\n";
			return;
		}
		if (hasLot3 && parkingLot3.xoaXe(id)) {
			cout << "Lay xe thanh cong!\n";
			return;
		}
		cout << "Khong tim thay xe!\n";
	}
	void hienThiTatCaBai() {
		if (!hasLot1 && !hasLot2 && !hasLot3) {
			cout << "Chua co bai do nao!\n";
			return;
		}
		if (hasLot1) {
			cout << "Bai " << parkingLot1.getMaBai()
				<< " | Kich thuoc: " << parkingLot1.getKichThuoc()
				<< " | So xe: " << parkingLot1.demXe() << endl;
		}
		if (hasLot2) {
			cout << "Bai " << parkingLot2.getMaBai()
				<< " | Kich thuoc: " << parkingLot2.getKichThuoc()
				<< " | So xe: " << parkingLot2.demXe() << endl;
		}
		if (hasLot3) {
			cout << "Bai " << parkingLot3.getMaBai()
				<< " | Kich thuoc: " << parkingLot3.getKichThuoc()
				<< " | So xe: " << parkingLot3.demXe() << endl;
		}
	}
	void hienThiXeTrongBai() {
		int id = nhapSoNguyen("Nhap ma bai do: ");
		if (hasLot1 && parkingLot1.getMaBai() == id) {
			parkingLot1.hienThiThongTinBai();
			return;
		}
		if (hasLot2 && parkingLot2.getMaBai() == id) {
			parkingLot2.hienThiThongTinBai();
			return;
		}
		if (hasLot3 && parkingLot3.getMaBai() == id) {
			parkingLot3.hienThiThongTinBai();
			return;
		}
		cout << "Khong tim thay bai do!\n";
	}
	void lietKeXeTheoLoai() {
		string loai = nhapChuoi("Nhap loai xe (Car/Motorcycle/Bicycle): ");
		Vehicle xeTam;
		xeTam.setLoaiXe(loai);
		loai = xeTam.getLoaiXe();
		if (loai == "") {
			cout << "Loai xe khong hop le!\n";
			return;
		}
		int tong = 0;
		if (hasLot1) tong = tong + inXeTheoLoai(parkingLot1, loai);
		if (hasLot2) tong = tong + inXeTheoLoai(parkingLot2, loai);
		if (hasLot3) tong = tong + inXeTheoLoai(parkingLot3, loai);
		if (tong == 0) {
			cout << "Khong co xe nao thuoc loai nay!\n";
		}
	}
	void baoCaoPhiTrungBinh() {
		cout << "\n===== PHI TRUNG BINH TOAN HE THONG =====\n";
		baoCaoToanHe("Car");
		baoCaoToanHe("Motorcycle");
		baoCaoToanHe("Bicycle");
		cout << "\n===== PHAN TICH THEO TUNG BAI =====\n";
		if (hasLot1) baoCaoMotBai(parkingLot1);
		if (hasLot2) baoCaoMotBai(parkingLot2);
		if (hasLot3) baoCaoMotBai(parkingLot3);
	}
public:
	SystemInterface() {
		hasLot1 = false;
		hasLot2 = false;
		hasLot3 = false;
	}
	void chayMenu() {
		cout << fixed << setprecision(2);
		int luaChon;
		do {
			cout << "\n========== QUAN LY BAI DO XE ==========\n";
			cout << "1. Tao bai do xe moi\n";
			cout << "2. Them xe vao bai do\n";
			cout << "3. Xoa mot bai do xe\n";
			cout << "4. Lay xe ra khoi bai do\n";
			cout << "5. Hien thi danh sach bai do\n";
			cout << "6. Hien thi xe theo bai do\n";
			cout << "7. Liet ke xe theo loai\n";
			cout << "8. Bao cao phi do xe trung binh\n";
			cout << "9. Thoat chuong trinh\n";
			luaChon = nhapSoNguyen("Nhap lua chon: ");
			switch (luaChon) {
			case 1: taoBaiDo(); break;
			case 2: themXeVaoHeThong(); break;
			case 3: xoaBaiDo(); break;
			case 4: layXeRa(); break;
			case 5: hienThiTatCaBai(); break;
			case 6: hienThiXeTrongBai(); break;
			case 7: lietKeXeTheoLoai(); break;
			case 8: baoCaoPhiTrungBinh(); break;
			case 9: cout << "Da thoat chuong trinh!\n"; break;
			default: cout << "Lua chon khong hop le!\n";
			}
		} while (luaChon != 9);
	}
};
int main() {
	SystemInterface system;
	system.chayMenu();
	return 0;
}
