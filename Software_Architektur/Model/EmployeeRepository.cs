using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using Model;

namespace Model
{
    public class EmployeeRepository { 
    

        private static EmployeeRepository instance = new EmployeeRepository();
        public static EmployeeRepository Instance => instance;

        Dictionary<int,Employee> HashmapRepo = new Dictionary<int, Employee>();

        public void AddEmployee(Employee employee) {
            // Validierung des Literaturobjekts
            // Überprüfung der Existenz
            if (employee == null)
                throw new NullReferenceException();
            // Überprüfung der Pflichtfelder
            if (string.IsNullOrWhiteSpace(employee.Vorname) || string.IsNullOrWhiteSpace(employee.Nachname) || string.IsNullOrWhiteSpace(employee.Wohnort) || string.IsNullOrWhiteSpace(employee.Strasse))
                throw new Exception("Pflichtfelder Vorname oder Nachname oder Straße und Hausnummer oder Wohnort nicht angegeben");
            // Übergabe an die Datenschicht
            HashmapRepo.Add(employee.Id, employee);
        }

        public void DeleteEmployee(int id)
        {
            if (HashmapRepo.ContainsKey(id))
                HashmapRepo.Remove(id);
            else throw new Exception(" Bitte wählen Sie zuerst einen Mitarbeiter aus.");
        }

        public void EditEmployee(Employee employee)
        {
            if (employee == null)
                throw new NullReferenceException();
            if (HashmapRepo.ContainsKey(employee.Id))
                HashmapRepo[employee.Id] = employee;
        }


        public List<Employee> GetEmployees()
        {
            
            List<Employee> resultList = new List<Employee>(HashmapRepo.Values);

            return resultList;
        }
    }
}