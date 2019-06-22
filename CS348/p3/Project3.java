import java.sql.*;
import java.io.*; 
import java.util.ArrayList;

public class Project3 {
	static final String USER = "shah255";
	static final String PASS = "LWU3lh39";
	static final String DB_URL = "jdbc:oracle:thin:@claros.cs.purdue.edu:1524:strep";
	File inputFile, outputFile;
	Connection dbCon = null;
	String contextUser;
	int contextUserId;

	public Project3(String inputFile, String outputFile){
		this.inputFile = new File(inputFile);
		this.outputFile = new File(outputFile);
		this.outputFile.delete();
		this.outputFile = new File(outputFile);
	}

	public void setConn(){
		Connection conn = null;
		try {
			Class.forName("oracle.jdbc.OracleDriver");
			this.dbCon = DriverManager.getConnection(DB_URL,USER,PASS);
		} catch (SQLException se){
			se.printStackTrace();
		} catch(Exception e){
			e.printStackTrace();
		}
	}

	public Connection getConn(){
		return this.dbCon;
	}

	public void closeConn(){
		try {
			this.dbCon.close();
		} catch(SQLException se){
		}
	}

	public ArrayList<String> fetchCommands(){
		ArrayList<String> sql = new ArrayList<String>();
		try {	
			BufferedReader br = new BufferedReader(new FileReader(inputFile)); 
			String st;
			while((st = br.readLine()) != null){
				sql.add(st);
			}
		} catch(Exception e){
			e.printStackTrace();
		}
		return sql;
	}
	
	public boolean checkAdmin(){
		boolean isAdmin = false;
		try {
			Statement stmt = this.getConn().createStatement();
			String tmpSql = "SELECT RoleName FROM UserRoles inner join Roles on UserRoles.RoleId = Roles.RoleId WHERE UserRoles.UserId = " + this.contextUserId;
			ResultSet rs = stmt.executeQuery(tmpSql);
			while(rs.next()){
				String RoleName = rs.getString("RoleName");
				if(RoleName.equals("ADMIN")){
					isAdmin = true;
					break;
				}
			}
			rs.close();
			stmt.close();
		} catch(SQLException se){
			se.printStackTrace();
		}
		return isAdmin;
	}

	public int detectQueryType(String sql){
		if(sql.contains("LOGIN")){
			return 0;
		} else if(sql.contains("CREATE ROLE")){
			return 1;
		} else if (sql.contains("CREATE USER")){
			return 2;
		} else if(sql.contains("ASSIGN ROLE")){
			return 3;
		} else if(sql.contains("GRANT PRIVILEGE")){
			return 4;
		} else if(sql.contains("REVOKE PRIVILEGE")){
			return 5;
		} else if(sql.contains("INSERT INTO")){
			return 6;
		} else if(sql.contains("SELECT")){
			return 7;
		} else if(sql.contains("EXIT")){
			return 8;
		}
		return -1;
	}

	public String runLogin(String sql){
		String result = "";
		try{
			Statement stmt = this.getConn().createStatement();
			String tmpSql = "SELECT * FROM Users";
			ResultSet rs = stmt.executeQuery(tmpSql);
			while(rs.next()){
				int uid = rs.getInt("UserId");
				String username = rs.getString("Username");
				String password = rs.getString("Password");
				String[] splitted = sql.split("\\s+");
				if(splitted.length != 3){
					result = "Invalid login";
				}
				if(username.equals(splitted[1]) && password.equals(splitted[2])){
					result = "Login successful";
					this.contextUser = username;
					this.contextUserId = uid;
					break;
				}else{
					result = "Invalid login";
				}
			}
			rs.close();
			stmt.close();
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}
	
	public String runRoleCreation(String sql){
		String result = "Authorization failure";
		try {
			if(this.checkAdmin()){
				String[] splitted = sql.split("\\s+");
				if(splitted.length != 3){
					result = "Authorization failure";
				} else{
					Statement stmt = this.getConn().createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
					String lastIdSql = "SELECT RoleId FROM Roles";
					ResultSet rs = stmt.executeQuery(lastIdSql);
					rs.last();
					int lastId = rs.getInt("RoleId");
					String insertSql = "INSERT INTO Roles VALUES (" + (lastId + 1) + ",\'" + splitted[2] + "\')";
					stmt.executeUpdate(insertSql);
					result = "Role created successfully";
					rs.close();
					stmt.close();
				}
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}
	
	public String runCreateUser(String sql){
		String result = "Authorization failure";
		try{
			if(this.checkAdmin()){
				String[] splitted = sql.split("\\s+");
				if(splitted.length == 4){
					Statement stmt = this.getConn().createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_READ_ONLY);
					String lastUidSql = "SELECT UserId FROM Users";
					ResultSet rs = stmt.executeQuery(lastUidSql);
					rs.last();
					int lastUid = rs.getInt("UserId");
					PreparedStatement pstmt = this.getConn().prepareStatement("INSERT INTO Users VALUES (?, ?, ?)");
					pstmt.setInt(1, lastUid + 1);
					pstmt.setString(2, splitted[2]);
					pstmt.setString(3, splitted[3]);
					pstmt.executeUpdate();
					result = "User created successfully";
					rs.close();
					stmt.close();
					pstmt.close();
				}
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}
	
	public String runAssignRole(String sql){
		String result = "Authorization failure";
		try {
			if(this.checkAdmin()){
				String[] splitted = sql.split("\\s+");
				if(splitted.length == 4){
					PreparedStatement pstmt = this.getConn().prepareStatement("SELECT RoleId FROM Roles WHERE RoleName = ?");
					pstmt.setString(1, splitted[3]);
					ResultSet r1 = pstmt.executeQuery();
					while(r1.next()){
						int roleId = r1.getInt("RoleId");
						PreparedStatement pstmt2 = this.getConn().prepareStatement("SELECT UserId FROM Users WHERE Username = ?");
						pstmt2.setString(1, splitted[2]);
						ResultSet r2 = pstmt2.executeQuery();
						while(r2.next()){
							int userId = r2.getInt("UserId");
							PreparedStatement ps = this.getConn().prepareStatement("INSERT INTO UserRoles VALUES (?, ?)");
							ps.setInt(1, userId);
							ps.setInt(2, roleId);
							ps.executeUpdate();
							result = "Role assigned successfully";
							ps.close();
						}
						r2.close();
						pstmt2.close();
					}
					r1.close();
					pstmt.close();
				}
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}

	public String runGrantPriv(String sql){
		String result = "Authorization failure";
		try {
			if(this.checkAdmin()){
				String[] splitted = sql.split("\\s+");
				if(splitted.length == 7){
					PreparedStatement pstmt1 = this.getConn().prepareStatement("SELECT PrivId FROM Privileges WHERE PrivName = ?");
					pstmt1.setString(1, splitted[2]);
					PreparedStatement pstmt2 = this.getConn().prepareStatement("SELECT RoleId FROM Roles WHERE RoleName = ?");
					pstmt2.setString(1, splitted[4]);
					ResultSet r1 = pstmt1.executeQuery();
					while(r1.next()){
						int privId = r1.getInt("PrivId");
						ResultSet r2 = pstmt2.executeQuery();
						while(r2.next()){
							int roleId = r2.getInt("RoleId");
							PreparedStatement ps = this.getConn().prepareStatement("INSERT INTO UserPrivileges VALUES (?, ?, ?)");
							ps.setInt(1, roleId);
							ps.setInt(2, privId);
							ps.setString(3, splitted[6]);
							ps.executeUpdate();
							result = "Privilege granted successfully";
							ps.close();
						}
						r2.close();
						pstmt2.close();
					}
					r1.close();
					pstmt1.close();
				}
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}

	public String runRevokePriv(String sql){
		String result = "Authorization failure";
		try {
			if(this.checkAdmin()){
				String[] splitted = sql.split("\\s+");
				if(splitted.length == 7){
					PreparedStatement pstmt1 = this.getConn().prepareStatement("SELECT PrivId FROM Privileges WHERE PrivName = ?");
					pstmt1.setString(1, splitted[2]);
					PreparedStatement pstmt2 = this.getConn().prepareStatement("SELECT RoleId FROM Roles WHERE RoleName = ?");
					pstmt2.setString(1, splitted[4]);
					ResultSet r1 = pstmt1.executeQuery();
					while(r1.next()){
						int privId = r1.getInt("PrivId");
						ResultSet r2 = pstmt2.executeQuery();
						while(r2.next()){
							int roleId = r2.getInt("RoleId");
							PreparedStatement ps = this.getConn().prepareStatement("DELETE FROM UserPrivileges WHERE RoleId = ? AND PrivId =  ? AND TableName = ?");
							ps.setInt(1, roleId);
							ps.setInt(2, privId);
							ps.setString(3, splitted[6]);
							ps.executeUpdate();
							result = "Privilege revoked successfully";
							ps.close();
						}
						r2.close();
						pstmt2.close();
					}
					r1.close();
					pstmt1.close();
				}
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}

	public String runInsert(String sql){
		String result = "Authorization failure";
		try{
			String valueList = sql.substring(sql.indexOf("("), sql.indexOf(")") + 1);
			String tmpSql = sql.replace(valueList + " ", "");
			String[] splitted = tmpSql.split("\\s+");
			if(splitted.length == 6){
				PreparedStatement pstmt1 = this.getConn().prepareStatement("SELECT PrivName FROM (UserPrivileges inner join UserRoles on UserPrivileges.RoleId = UserRoles.RoleId) inner join Privileges on Privileges.PrivId = UserPrivileges.PrivId WHERE UserRoles.UserId = ? AND UserPrivileges.TableName = ?");
				pstmt1.setInt(1, this.contextUserId);
				pstmt1.setString(2, splitted[2]);
				ResultSet r1 = pstmt1.executeQuery();
				while(r1.next()){
					if(r1.getString("PrivName").equals("INSERT")){
						PreparedStatement pstmt2 = this.getConn().prepareStatement("SELECT RoleId FROM Roles WHERE RoleName = ?");
						pstmt2.setString(1, splitted[5]);
						ResultSet r2 = pstmt2.executeQuery();
						while(r2.next()){
							String valueListOwnerRole = valueList.substring(0, valueList.indexOf(')')) + ", " + r2.getInt("RoleId") + ")";
							Statement stmt = this.getConn().createStatement();
							stmt.executeUpdate("INSERT INTO " + splitted[2] + " VALUES " + valueListOwnerRole);
							result = "Row inserted successfully";
							stmt.close();
							break;
						}
						r2.close();
						pstmt2.close();
					}
				}
				r1.close();
				pstmt1.close();
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}

	public String runSelect(String sql){
		String result = "Authorization failure";
		try {
			String[] splitted = sql.split("\\s+");
			if(splitted.length == 4){
				PreparedStatement pstmt1 = this.getConn().prepareStatement("SELECT PrivName FROM (UserPrivileges inner join UserRoles on UserPrivileges.RoleId = UserRoles.RoleId) inner join Privileges on Privileges.PrivId = UserPrivileges.PrivId WHERE UserRoles.UserId = ? AND UserPrivileges.TableName = ?");
				pstmt1.setInt(1, this.contextUserId);
				pstmt1.setString(2, splitted[3]);
				ResultSet r1 = pstmt1.executeQuery();
				while(r1.next()){
					if(r1.getString("PrivName").equals("SELECT")){
						Statement stmt = this.getConn().createStatement();
						ResultSet r2 = stmt.executeQuery(sql);
						ResultSetMetaData rsmd = r2.getMetaData();
						int numberOfColumns = rsmd.getColumnCount();
						String metaDataString = "";
						ArrayList<String> columnNames = new ArrayList<String>();
						for(int i = 0; i < numberOfColumns; i++){
							String columnLabel = rsmd.getColumnLabel(i + 1).toUpperCase();
							if(!columnLabel.equals("OWNERROLE")){
								metaDataString +=  columnLabel + ",";
								columnNames.add(columnLabel);
							}
						}
						if(metaDataString.charAt(metaDataString.length() - 1) == ','){
							metaDataString = metaDataString.substring(0, metaDataString.length() - 1);
						}
						metaDataString = metaDataString.replaceAll(",", ", ");
						String dataString = "";
						while(r2.next()){
							for(int i = 0; i < columnNames.size(); i++){
								dataString += r2.getString(columnNames.get(i)) + ", ";
							}
							if(dataString.charAt(dataString.length() - 2) == ','){
								dataString = dataString.substring(0, dataString.length() - 2);
							}
							//dataString = dataString.replaceAll(",", ", ");
							dataString += "\n";
						}
						result = metaDataString + "\n" + dataString;
						result = result.substring(0, result.length() - 1);
						r2.close();
						stmt.close();
					}
				}
				r1.close();
				pstmt1.close();
			}
		} catch(SQLException se){
			se.printStackTrace();
		}
		return result;
	}

	public void runExit(String sql){
		System.exit(0);
	}
	
	public void outputWriter(String stringToWrite){
		try{
			if(!this.outputFile.exists()){
				this.outputFile.createNewFile();
			}
			FileWriter fw = new FileWriter(this.outputFile, true);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(stringToWrite);
			bw.close();
			fw.close();
		} catch(Exception e){
			e.printStackTrace();
		}
	}

	public static void main(String[] args){
		if(args.length != 2){
			System.out.println("Invalid number of arguments");
			System.exit(-1);
		}
		
		Project3 p3 = new Project3(args[0], args[1]);
		//System.out.println("Connecting to database...");
		p3.setConn();
		ArrayList<String> allSql = p3.fetchCommands();
		for(int s = 0; s < allSql.size(); s++){
			int sqlType = p3.detectQueryType(allSql.get(s));
			String queryResult = "";
			String metaString = "" + (s + 1) + ": " + allSql.get(s) + "\n";
			p3.outputWriter(metaString);
			if(sqlType == 0){
				queryResult = p3.runLogin(allSql.get(s));
			} else if(sqlType == 1){
				queryResult = p3.runRoleCreation(allSql.get(s)); 
			} else if(sqlType == 2){
				queryResult = p3.runCreateUser(allSql.get(s));
			} else if(sqlType == 3){
				queryResult = p3.runAssignRole(allSql.get(s));
			} else if(sqlType == 4){
				queryResult = p3.runGrantPriv(allSql.get(s));
			} else if(sqlType == 5){
				queryResult = p3.runRevokePriv(allSql.get(s));
			} else if(sqlType == 6){
				queryResult = p3.runInsert(allSql.get(s));
			} else if(sqlType == 7){
				queryResult = p3.runSelect(allSql.get(s));
			} else if(sqlType == 8){
				p3.runExit(allSql.get(s));
			}
			p3.outputWriter(queryResult + "\n\n");
			//System.out.println(allSql.get(s) + " : " + queryResult);
		}
		p3.closeConn();
	}
}
