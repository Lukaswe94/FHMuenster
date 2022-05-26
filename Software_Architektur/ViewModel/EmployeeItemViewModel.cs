using System;
using System.ComponentModel;


namespace ViewModel
{
    public class EmployeeItemViewModel : INotifyPropertyChanged
    {
        private int id;
        private string vorname;
        private string nachname;
        private string wohnort;
        private int plz;
        private string strasse;
        private DateTime datum = DateTime.Today; 

        public event PropertyChangedEventHandler PropertyChanged;

        #region Properties
        public int Id
        {
            get { return this.id; }
            set
            {
                if (this.id != value)
                {
                    this.id = value;
                    this.OnPropertyChanged(nameof(Id));
                    this.OnPropertyChanged(nameof(ShortInfo));
                }
            }
        }


        public string Vorname
        {
            get { return this.vorname; }
            set
            {
                if (this.vorname != value)
                {
                    this.vorname = value;
                    this.OnPropertyChanged(nameof(Vorname));
                    this.OnPropertyChanged(nameof(ShortInfo));   
                }
            }
        }

        public string Nachname
        {
            get { return this.nachname; }
            set
            {
                if (this.nachname != value)
                {
                    this.nachname = value;
                    this.OnPropertyChanged(nameof(nachname));
                    this.OnPropertyChanged(nameof(ShortInfo));    
                }
            }
        }

        public string Wohnort
        {
            get { return this.wohnort; }
            set
            {
                if (this.wohnort != value)
                {
                    this.wohnort = value;
                    this.OnPropertyChanged(nameof(Wohnort));
                    this.OnPropertyChanged(nameof(ShortInfo));
                }
            }
        }

        public string Strasse
        {
            get { return this.strasse; }
            set
            {
                if (this.strasse != value)
                {
                    this.strasse = value;
                    this.OnPropertyChanged(nameof(Strasse));
                    this.OnPropertyChanged(nameof(ShortInfo));   
                }
            }
        }

        public int Plz 
        {
            get { return this.plz; }
            set
            {
                if (this.plz != value)
                {
                    this.plz = value;
                    this.OnPropertyChanged(nameof(Plz));
                    this.OnPropertyChanged(nameof(ShortInfo));   
                }
            }
        }

        public DateTime Datum
        {
            get { return this.datum; }
            set
            {
                if (this.datum != value)
                {
                    this.datum = value;
                    this.OnPropertyChanged(nameof(Datum));
                    this.OnPropertyChanged(nameof(ShortInfo));  
                }
            }
        }

        public string ShortInfo
        {
            get
            {
                return string.Format("{0} {1}, wohnhaft in  {2}, {3} {4}. ({5})", this.Vorname, this.Nachname, this.Strasse, this.Wohnort, this.Plz, this.Datum);
            }
        }

        #endregion


        public void Clear()
        {
            this.Id = 0;
            this.Vorname = null;
            this.Nachname = null;
            this.Wohnort = null;
            this.Plz = 0;
            this.Strasse = null;
            this.Datum = default(DateTime);
        }

        protected void OnPropertyChanged(string propertyName)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
