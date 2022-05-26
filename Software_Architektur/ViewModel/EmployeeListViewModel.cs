//  using Model ;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Linq;
using System.Windows.Input;
using System.ComponentModel;
using Model;

namespace ViewModel
{
    /// <summary>
    /// Anzeigemodell für die Darstellung einer Mitarbeiterliste und die Eingabe eines neuen Mitarbeiter-Datensatzes  
    /// </summary>
    public class EmployeeListViewModel : INotifyPropertyChanged 
    {
        #region Fields 
        private ObservableCollection<EmployeeItemViewModel> items;
        private EmployeeItemViewModel itemToAdd;
        private EmployeeItemViewModel selectedItem;
        private string errorMessage;
        public int index=0;
        public string Filter { get; set; }
        #endregion

        #region  Constructors

        public EmployeeListViewModel()
        {
            // Initialisierung der Mitarbeiterliste mit einer leeren Liste
            this.Items = new ObservableCollection<EmployeeItemViewModel>();
            // Init ItemToAdd with empty Instance
            this.ItemToAdd = new EmployeeItemViewModel();

            // Verknüpfung der Commands mit den angegebenen Methoden
            
            this.AddCommand = new RelayCommand(this.AddItem);
            this.DeleteCommand = new RelayCommand(this.DeleteItem);
            this.EditCommand = new RelayCommand(this.EditItem);
            this.RefreshCommand = new RelayCommand(this.DoRefresh);
            this.FilterCommand = new RelayCommand(this.FilterByWohnort);

        }

        #endregion

        #region Properties

        public event PropertyChangedEventHandler PropertyChanged;

        #region Commands

        /// <summary>
        /// Command zum Hinzufügen eines neuen Eintrags aus den Formularwerten
        /// </summary>
        public ICommand AddCommand { get; private set; }


        /// <summary>
        /// Command zum Löschen eines Eintrags aus der Listenanzeige
        /// </summary>
        public ICommand DeleteCommand { get; private set; }


        /// <summary>
        /// Command zur Aktualisierung der Listenanzeige
        /// </summary>
        public ICommand EditCommand { get; private set; }

        public ICommand RefreshCommand { get; private set; }
        #endregion
        public ICommand FilterCommand { get; private set; }

        /// <summary>
        /// Liste der Literatureinträge für die Anzeige
        /// </summary>
        public ObservableCollection<EmployeeItemViewModel> Items
        {
            get
            {
                return this.items;
            }
            set
            {
                if (this.items != value)
                {
                    this.items = value;
                    this.OnPropertyChanged(nameof(Items));
                }
            }
        }

        /// <summary>
        /// Literatur-Element mit Daten zur Anlage eines neuen Datensatzes
        /// </summary>
        public EmployeeItemViewModel ItemToAdd
        {
            get
            {
                return this.itemToAdd;
            }
            set
            {
                if (this.itemToAdd != value)
                {
                    this.itemToAdd = value;
                    this.OnPropertyChanged(nameof(ItemToAdd));
                }
            }
        }

        public EmployeeItemViewModel SelectedItem
        {
            get
            {
                return this.selectedItem;
            }
            set
            {
                if (this.selectedItem != value)
                {
                    this.selectedItem = value;
                    this.OnPropertyChanged(nameof(SelectedItem));
                }
            }
        }

        /// <summary>
        /// Fehlermeldung für die Anzeige
        /// </summary>
        public String ErrorMessage
        {
            get { return this.errorMessage; }
            set
            {
                if (this.errorMessage != value)
                {
                    this.errorMessage = value;
                    this.OnPropertyChanged(nameof(ErrorMessage));
                }

            }
        }

        /// <summary>
        /// Propagation der Änderungen von Eigenschaftswerten
        /// </summary>
        /// <param name="propertyName"></param>
        protected void OnPropertyChanged(string propertyName)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion

        #region Methods

        // Interne Methode, um das aktuelle Literaturelement zum Model hinzuzufügen
        private void AddItem(object obj) 
        {
            this.index++;
            try
            {
                if (ItemToAdd != null)
                    this.ItemToAdd.Id = this.index;
                else throw new Exception(" Bitte füllen Sie die Felder aus.");
            }
            catch (Exception e)
            {
                this.ErrorMessage = e.Message;
            }


            // Übertragen der ViewModel-Daten in das Model
            //if (this.ItemToAdd != null)

            Employee employee = new Employee()
                {   
                    Id = this.index,
                    Vorname = this.ItemToAdd.Vorname,
                    Nachname = this.ItemToAdd.Nachname,
                    Wohnort = this.ItemToAdd.Wohnort,
                    Plz = (int)this.ItemToAdd.Plz,
                    Strasse = this.ItemToAdd.Strasse,
                    Datum = this.ItemToAdd.Datum

                };




                try
                {
                    // Übergabe an das Model zur Verarbeitung
                    // Zugriff / Referenz auf das Model kann auch per DI / IoC entkoppelt werden
                    EmployeeRepository.Instance.AddEmployee(employee);
                    // Aktualisierung des Darstellungszustands
                    this.Items.Add(this.ItemToAdd);
                    this.ItemToAdd = new EmployeeItemViewModel();
                    this.ErrorMessage = null;
                }
                catch (Exception e)
                {
                    this.ErrorMessage = e.Message;
                }
            
        }

        private void DeleteItem(object obj)
        {

            try
            {
                // Übergabe an das Model zur Verarbeitung
                if(SelectedItem != null)
                EmployeeRepository.Instance.DeleteEmployee(SelectedItem.Id);
                else throw new Exception("Bitte wählen Sie zuerst einen Mitarbeiter aus.");

                // Aktualisierung des Darstellungszustands
                this.Items.Remove(this.SelectedItem);
                this.SelectedItem = new EmployeeItemViewModel();
                this.ErrorMessage = null;
            }
            catch (Exception e)
            {
                this.ErrorMessage = e.Message;
            }
        }


        private void EditItem(object obj)
        {

            this.ItemToAdd = this.SelectedItem;
            
            try
            {
                    if (SelectedItem != null)
                    EmployeeRepository.Instance.DeleteEmployee(SelectedItem.Id);
                    else throw new Exception("Bitte wählen Sie zuerst einen Mitarbeiter aus.");
            }
            catch (Exception e)
            {
                this.ErrorMessage = e.Message;
                this.ItemToAdd = new EmployeeItemViewModel();

            }
            
            this.Items.Remove(this.SelectedItem);
                
            
            
   
        }
        
        private void FilterByWohnort(object obj)
        {
            if (Filter == null)
            {
                this.ErrorMessage = "Bitte tragen Sie einen Wohnort ein";
                return;
            }
            //this.ErrorMessage = null;
            
            List<Employee> modelItems = EmployeeRepository.Instance.GetEmployees();
            List<Employee> filteredItems = modelItems.FindAll(employee => employee.Wohnort.ToLower().Contains(this.Filter.ToLower()));
            var viewModelItems = filteredItems.Select(employee
                => new EmployeeItemViewModel()
                {
                    Id = employee.Id,
                    Vorname = employee.Vorname,
                    Nachname = employee.Nachname,
                    Wohnort = employee.Wohnort,
                    Plz = employee.Plz,
                    Strasse = employee.Strasse,
                    Datum = employee.Datum
                });
            this.Items = new ObservableCollection<EmployeeItemViewModel>(viewModelItems);
            
        }
        

        private void DoRefresh(object obj)              
        {
            
            List<Employee> modelItems = EmployeeRepository.Instance.GetEmployees(); 
            // Model-Daten in die ViewModel-Einträge übertragen
            var viewModelItems = modelItems.Select(employee
                => new EmployeeItemViewModel()
                {   Id = employee.Id,
                    Vorname = employee.Vorname,
                    Nachname = employee.Nachname,
                    Wohnort = employee.Wohnort,
                    Plz = employee.Plz,
                    Strasse = employee.Strasse,
                    Datum = employee.Datum
                });
            this.Items = new ObservableCollection<EmployeeItemViewModel>(viewModelItems);
        }

        #endregion
    }
}
